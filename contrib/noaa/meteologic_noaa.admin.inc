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

  $form['wrapper']['current']['meteologic_noaa_current_path'] = array(
    '#title' => t('Path'),
    '#description' => t('Alter the path for the NOAA Current Conditions feed.'),
    '#type' => 'textfield',
    '#default_value' => variable_get_value('meteologic_noaa_current_path'),
    '#required' => TRUE,
    '#weight' => 10,
  );

  return system_settings_form($form);
}