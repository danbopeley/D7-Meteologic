<?php
/**
 * @file
 * Meteologic admin pages.
 */

/**
 * Form callback.
 * Displays meteologic global settings form.
 *
 * @see meteologic_menu()
 */
function meteologic_form_settings() {
  $form = array();

  $form['blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blocks'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['blocks']['meteologic_feed_blocks'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate a block for each feed and provider'),
    '#description' => t('By default only a single block for each feed is generated, using the selected provider. Check ths option so that regardless of which feeds and providers are enabled, a block will generated each valid combination.'),
    '#default_value' => variable_get('meteologic_feed_blocks', FALSE),
  );

  $form['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['pages']['meteologic_page_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable pages'),
    '#description' => t('Enable this to get pages as well as blocks for each meteologic feed.'),
    '#default_value' => variable_get('meteologic_page_enable', FALSE),
  );

  $form['pages']['metelogic_page_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Base path for pages'),
    '#description' => t('Define a base path for Meteologic feed pages. The default is "meteologic", so each feed will have a URL like this: meteologic/current, meteologic/radar and so on. Please not that this path will only be used as a base and will have no page of its own.'),
    '#default_value' => variable_get('metelogic_page_path', 'meteologic'),
    '#states' => array(
      'visible' => array(
        'input[name="meteologic_page_enable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['pages']['meteologic_feed_pages'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate a page for each feed and provider'),
    '#description' => t('By default only a single page for each feed is generated, using the selected provider. Check ths option so that regardless of which feeds and providers are enabled, a page will generated for each valid combination.'),
    '#default_value' => variable_get('meteologic_feed_pages', FALSE),
    '#states' => array(
      'visible' => array(
        'input[name="meteologic_page_enable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Misc'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['misc']['meteologic_dev'] = array(
    '#type' => 'checkbox',
    '#title' => t('Development mode'),
    '#description' => t('Development mode logs more watchdog entries such as debug statments whereas production will only log errors.'),
    '#default_value' => variable_get('meteologic_dev', TRUE),
  );

  $form['#submit'][] = 'meteologic_form_settings_submit';

  return system_settings_form($form);
}

/**
 * Submit callback.
 * We need to rebuild the menu if the "pages" option changes.
 *
 * @see meteologic_form_settings()
 */
function meteologic_form_settings_submit(&$form, &$form_state) {
  $page_enable = variable_get('meteologic_page_enable', FALSE);

  // Value changed, must reubuild menu.
  if ($page_enable != $form_state['values']['meteologic_page_enable']) {
    variable_set('menu_rebuild_needed', TRUE);
  }
  // Value didn't change but is on; check whether the generate page for each
  // feed/provider combo changed as it will also warrant a menu rebuild.
  else if ($form_state['values']['meteologic_page_enable']) {
    $page_combo = variable_get('meteologic_feed_pages', FALSE);

    if ($page_combo != $form_state['values']['meteologic_feed_pages']) {
      variable_set('menu_rebuild_needed', TRUE);
    }
  }
}

/**
 * Form callback.
 * Displays meteologic cron settings form.
 *
 * @see meteologic_menu()
 */
function meteologic_form_settings_cron() {
  $form = array();

  $form['cron'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cron'),
    '#description' => t("Here you can manually configure which feeds from which providers are updated, if any, during cron. Please note that regardless of what is selected here, if a provider isn't enabled for that feed it won't get updated.."),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  foreach (meteologic_feeds() as $feed => $feed_info) {
    if (!empty($feed_info['providers'])) {

      $form['cron'][$feed] = array(
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
//        '#collapsed' => TRUE,
        '#title' => $feed_info['name'],
        '#tree' => TRUE,
      );

      foreach ($feed_info['providers'] as $provider => $provider_info) {
        if ($provider_info['enabled']) {
          $varname = "meteologic_cron_{$feed}_{$provider}";

          $form['cron'][$feed][$provider] = array(
            '#type' => 'checkbox',
            '#title' => $provider_info['name'],
            '#default_value' => variable_get($varname, TRUE),
          );
        }
      }
    }
  }

  $form['#submit'][] = 'meteologic_form_settings_cron_submit';

  return system_settings_form($form);
}

/**
 * Submit callback.
 * I'm not sure why we need this but the form wasn't saving variables any other
 * way. @TODO come back to this later.
 */
function meteologic_form_settings_cron_submit(&$form, &$form_state) {
  foreach ($form_state['values']['cron'] as $feed => $feed_info) {
    foreach ($feed_info as $provider => $status) {
      $varname = "meteologic_cron_{$feed}_{$provider}";
      variable_set($varname, $status);
    }
  }
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
  drupal_set_title(t('Meteologic Feeds - @name feed', array('@name' => $feed_info['name'])));

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
      '#default_value' => variable_get($varname, FALSE),
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

    if (empty($weights)) {
      // This option hasn't been set yet, so manually populate the
      // providers that implement this feed.
      foreach ($feed_info['providers'] as $provider) {
        $weights[$provider] = 0;
      }
    }

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

  if (isset($values['providers'])) {
    // Provider order.
    $order = array();

    foreach ($values['providers'] as $slug => $info) {
      $order[$slug] = $info['weight'];
    }

    asort($order);
    variable_set("meteologic_weight_{$feed}", $order);
  }
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
  $providers = meteologic_providers();

  // Only display feeds with at least one provider.
  $update_feeds = array();
  $update_providers = array();

  foreach (meteologic_feeds() as $feed_slug => $feed_info) {
    if (!empty($feed_info['providers'])) {
      $update_feeds[$feed_slug] = $feed_info['name'];
      foreach ($feed_info['providers'] as $provider) {
        if (isset($providers[$provider])) {
          $update_providers[$provider] = $providers[$provider]['name'];
        }
      }
    }
  }

  $form['feeds'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Feeds'),
    '#description' => t('Select which feeds to update'),
    '#options' => $update_feeds,
    '#default_value' => array_keys($update_feeds),
  );

  $form['providers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Providers'),
    '#description' => t('Select which providers to update'),
    '#options' => $update_providers,
    '#default_value' => array_keys($update_providers),
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
  $feeds = $form_state['values']['feeds'];
  $providers = $form_state['values']['providers'];

  include_once drupal_get_path('module', 'devel') . '/krumo/class.krumo.php';
//  krumo($feeds, $providers);die;

  meteologic_update_feeds($feeds, $providers);
}