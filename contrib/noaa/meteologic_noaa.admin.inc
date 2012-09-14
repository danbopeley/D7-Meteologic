<?php
/**
 * @file
 * Meteologic NOAA settings pages.
 */

/**
 * Form callback.
 * Display settings form for Meteologic Mesowest.
 */
function meteologic_noaa_settings_form() {
  $form = array();

  $form['wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('NOAA Settings'),
    '#collapsible' => FALSE,
  );

  // Current conditions feed settings.
  $form['wrapper']['current'] = array(
    '#type' => 'fieldset',
    '#title' => t('Current Conditions'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Get a list of placeholder tokens.
  $provider = meteologic_providers('noaa');
  $tokens = implode(', ', $provider['feeds']['current']['tokens']);

  $form['wrapper']['current']['meteologic_noaa_current_path'] = array(
    '#title' => t('Path'),
    '#description' => t('Alter the path for the NOAA Current Conditions feed. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
    '#type' => 'textfield',
    '#default_value' => variable_get_value('meteologic_noaa_current_path'),
    '#required' => TRUE,
    '#weight' => 10,
  );

  // Point forecast feed settings.
  $form['wrapper']['forecast'] = array(
    '#type' => 'fieldset',
    '#title' => t('Point Forecast'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Get a list of placeholder tokens.
  $provider = meteologic_providers('noaa');
  $tokens = implode(', ', $provider['feeds']['forecast']['tokens']);

  $form['wrapper']['forecast']['meteologic_noaa_forecast_path'] = array(
    '#title' => t('Path'),
    '#description' => t('Alter the path for the NOAA Point Forecast feed. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
    '#type' => 'textfield',
    '#default_value' => variable_get_value('meteologic_noaa_forecast_path'),
    '#required' => TRUE,
    '#weight' => 10,
  );

  return system_settings_form($form);
}