<?php
/**
 * @file
 * Meteologic MesoWest settings pages.
 */

/**
 * Form callback.
 * Display settings form for Meteologic Mesowest.
 */
function meteologic_mesowest_settings_form() {
  $form = array();

    // Grab provider info.
  $provider = meteologic_providers('mesowest');

  $form['wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mesowest Settings'),
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
  $tokens = implode(', ', $provider['feeds']['current']['tokens']);
  
  $form['wrapper']['current']['meteologic_mesowest_current_path'] = array(
      '#title' => t('Path'),
      '#description' => t('Alter the path for the Mesowest Conditions feed. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_mesowest_current_path'),
      '#size' => 120,
      '#required' => TRUE,
  );
  
  $stations = call_user_func($provider['feeds']['current']['stations']);
  
  $form['wrapper']['current']['meteologic_mesowest_current_station'] = array(
      '#title' => t('Station'),
      '#description' => t(''),
      '#type' => 'select',
      '#options' => $stations,
      '#default_value' => variable_get_value('meteologic_mesowest_current_station'),
  );

  return system_settings_form($form);
}