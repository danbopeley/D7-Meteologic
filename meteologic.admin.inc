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
function meteologic_settings_form() {
  $form = array();

  // @TODO add vars as we know em.

  return system_settings_form($form);
}

/**
 * Page callback.
 * Displays meteologic provider settings home page.
 *
 * @see meteologic_menu()
 */
function meteologic_providers_page() {
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
 * Displays meteologic summary page.
 *
 * @see meteologic_menu()
 */
function meteologic_summary_page() {
  drupal_set_title(t('Meteologic Summary'));
  $page = array();

  $feeds = meteologic_feeds();
  $page['types'] = array(
    '#theme' => 'item_list',
    '#items' => !empty($feeds) ? $feeds : array(t('-none-')),
    '#title' => t('Forecast Types'),
    '#type' => 'ul',
  );

  $providers = array();
  foreach (meteologic_providers() as $provider) {
    $providers[] = $provider['name'];
  }

  $page['providers'] = array(
    '#theme' => 'item_list',
    '#items' => !empty($providers) ? $providers : array(t('-none-')),
    '#title' => t('Forecast Providers'),
    '#type' => 'ul',
  );

  return $page;
}

/**
 * Form callback.
 * Displays update forecast feeds form.
 */
function meteologic_update_form() {
  $form = array();

  $options = array();
  foreach (meteologic_providers() as $provider_slug => $provider_info) {
    $options[$provider_slug] = $provider_info['name'];
  }

  $form['providers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Forecast Providers'),
    '#description' => t('Select which forecast providers to manually update'),
    '#options' => $options,
    '#default_value' => array_keys($options),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update forecasts'),
  );

  $form['#submit'] = array('meteologic_update_form_submit');
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

  meteologic_update_forecasts($providers);
}