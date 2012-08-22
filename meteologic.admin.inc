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
 * Form callback.
 * Displays meteologic summary page.
 */
function meteologic_summary_page() {
  drupal_set_title(t('Meteologic Summary'));
  $page = array();

  $types = meteologic_forecast_types();
  $page['types'] = array(
    '#theme' => 'item_list',
    '#items' => !empty($types) ? $types : array(t('-none-')),
    '#title' => t('Forecast Types'),
    '#type' => 'ul',
  );

  $providers = array();
  foreach (meteologic_forecast_providers() as $provider) {
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
  foreach (meteologic_forecast_providers() as $provider_slug => $provider_info) {
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