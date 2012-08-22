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