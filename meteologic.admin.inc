<?php
/**
 * @file
 * Meteologic admin pages.
 */

/**
 * Form callback.
 * Displays main meteologic settings form.
 *
 * @see meteologic_menu()
 */
function meteologic_form_settings() {
  $form = array();

  $form['meteologic_feed_blocks'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate a block for each feed and provider'),
    '#description' => t('Regardless of which feeds and providers are enabled, generate a block for each valid combination.'),
    '#default_value' => variable_get('meteologic_feed_blocks', FALSE),
  );

  $form['meteologic_feed_pages'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate a page for each feed and provider'),
    '#description' => t('Regardless of which feeds and providers are enabled, generate a page for each valid combination.'),
    '#default_value' => variable_get('meteologic_feed_pages', FALSE),
  );

  $form['meteologic_dev'] = array(
    '#type' => 'checkbox',
    '#title' => t('Development mode'),
    '#description' => t('Development mode logs more watchdog entries such as debug statments whereas production will only log errors.'),
    '#default_value' => variable_get('meteologic_dev', TRUE),
  );

  return system_settings_form($form);
}

/**
 * Page callback.
 * Displays meteologic provider settings home page.
 *
 * @see meteologic_menu()
 */
function meteologic_page_providers() {
  drupal_set_title(t('Meteologic Providers'));
  $page = array();

  $links = array();
  foreach (meteologic_providers() as $name => $info) {
    if (isset($info['settings']) && !empty($info['settings'])) {
      $links[] = array(
        'title' => $info['name'],
        'href' => "admin/config/services/meteologic/providers/{$name}",
      );
    }
  }

  $page['providers'] = array(
    '#theme' => 'links',
    '#links' => $links,
    '#heading' => t('Configure settings for Meteologic providers'),
    '#attributes' => array('id' => 'meteologic-settings-providers'),
  );

  return $page;
}

/**
 * Page callback.
 * Displays meteologic feeds settings home page.
 *
 * @see meteologic_menu()
 */
function meteologic_page_feeds() {
  drupal_set_title(t('Meteologic Feeds'));
  $page = array();

  $links = array();
  foreach (meteologic_feeds() as $name => $info) {
    $links[] = array(
      'title' => $info['name'],
      'href' => "admin/config/services/meteologic/feeds/{$name}",
    );
  }

  $page['feeds'] = array(
    '#theme' => 'links',
    '#links' => $links,
    '#heading' => t('Configure settings for Meteologic feeds'),
    '#attributes' => array('id' => 'meteologic-settings-feeds'),
  );

  return $page;
}

/**
 * Form callback.
 * Display feed config form.
 *
 * @see meteologic_menu()
 */
function meteologic_form_feed_config($form, &$form_state, $feed) {
  $form = array();
  $feed_info = meteologic_feeds($feed);
  drupal_set_title(t('Meteologic - @name feed', array('@name' => $feed_info['name'])));

  $form['enabled'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enabled Providers'),
    '#description' => t('Enable or disable providers for the @name feed.', array('@name' => $feed_info['name'])),
    '#collapsible' => FALSE,
    '#tree' => TRUE,
  );

  $varname = "meteologic_fallback_{$feed}";
  $form_state['meteologic_feed'] = $feed;

  $meteologic_providers = meteologic_providers();

  foreach ($feed_info['providers'] as $slug) {
    $varname = "meteologic_{$feed}_{$slug}";

    $form['enabled'][$varname] = array(
      '#type' => 'checkbox',
      '#title' => $meteologic_providers[$slug]['name'],
      '#default_value' => variable_get($varname, TRUE),
    );
  }

  if (count($feed_info['providers']) > 0) {
    $form['order'] = array(
      '#type' => 'fieldset',
      '#title' => t('Provider priority'),
      '#description' => t('If multiple providers are enabled, which one should we use?'),
      '#collapsible' => FALSE,
    );

    $form['order']['meteologic_fallback_current'] = array(
      '#type' => 'checkbox',
      '#title' => t('Fallback if unavailable'),
      '#description' => t('If the selected provider is unavailable, display the results for the next available one.'),
      '#default_value' => variable_get('meteologic_fallback_current', FALSE),
    );

    $form['order']['providers'] = array(
      '#tree' => TRUE,
    );

    $weights = variable_get("meteologic_weight_{$feed}", array());

    foreach ($weights as $slug => $weight) {
      $form['order']['providers'][$slug] = array(
        'name' => array(
          '#markup' => $meteologic_providers[$slug]['name'],
        ),
        'weight' => array(
          '#type' => 'weight',
          '#title' => t('Weight'),
          '#default_value' => $weight,
          '#delta' => 10,
          '#title-display' => 'invisible',
        ),
      );
    }
  }
  else {
    $form['enabled']['empty'] = array(
      '#prefix' => '<div class="empty">',
      '#suffix' => '</div>',
      '#markup' => t('No providers implement this feed!'),
    );
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Changes')
  );

  return $form;
}

/**
 * Submit callback.
 *
 * @see meteologic_form_feed_config()
 */
function meteologic_form_feed_config_submit(&$form, &$form_state) {
  $values = & $form_state['values'];
  $feed = $form_state['meteologic_feed'];

  // Fallback variable.
  $varname = "meteologic_fallback_{$feed}";
  variable_set($varname, $values[$varname]);

  // Enabled providers.
  foreach ($values['enabled'] as $provider => $status) {
    variable_set($provider, $status);
  }

  // Provider order.
  $order = array();

  foreach ($values['providers'] as $slug => $info) {
    $order[$slug] = $info['weight'];
  }

  asort($order);
  variable_set("meteologic_weight_{$feed}", $order);
}

/**
 * Page callback.
 * Displays meteologic summary page.
 *
 * @see meteologic_menu()
 */
function meteologic_summary_page() {
  drupal_set_title(t('Meteologic Summary'));
  $meteologic_providers = meteologic_providers();
  $page = array();

  $header = array(t('Feed'));
  $rows = array();

  foreach ($meteologic_providers as $provider) {
    $header[] = $provider['name'];
  }

  foreach (meteologic_feeds() as $feed_slug => $feed) {
    $temp = array($feed['name']);

    foreach ($meteologic_providers as $provider) {
      if (array_key_exists($feed_slug, $provider['feeds'])) {
        $temp[] = 'x';
      }
      else {
        $temp[] = '';
      }
    }

    $rows[] = $temp;
  }

  $page['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  return $page;
}

/**
 * Form callback.
 * Displays update forecast feeds form.
 */
function meteologic_update_form() {
  $form = array();

  $feeds = array();
  foreach (meteologic_feeds() as $feed_slug => $feed_info) {
    $feeds[$feed_slug] = $feed_info['name'];
  }

  $form['feeds'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Feeds'),
    '#description' => t('Select which feeds to update'),
    '#options' => $feeds,
    '#default_value' => array_keys($feeds),
  );

  $providers = array();
  foreach (meteologic_providers() as $provider_slug => $provider_info) {
    $providers[$provider_slug] = $provider_info['name'];
  }

  $form['providers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Providers'),
    '#description' => t('Select which providers to update'),
    '#options' => $providers,
    '#default_value' => array_keys($providers),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update Feeds')
  );

  return $form;
}

/**
 * Submit callback.
 * Triggers updates for the selected forecast providers.
 *
 * @see meteologic_update_form()
 */
function meteologic_update_form_submit($form, &$form_state) {
  $providers = array();

  foreach ($form_state['values']['providers'] as $provider => $status) {
    if ($status) {
      $providers[] = $provider;
    }
  }

  meteologic_update_feeds($providers);
}