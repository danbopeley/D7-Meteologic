<?php
/**
 * @file
 * Meteologic MesoWest settings pages.
 */

/**
 * Form callback.
 * Display settings form for Meteologic Mesowest.
 */
function meteologic_ndbc_settings_form() {
  $form = array();

    // Grab provider info.
  $provider = meteologic_providers('ndbc');

  $form['wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mesowest Settings'),
    '#collapsible' => FALSE,
  );

  // Current conditions feed settings.
  $form['wrapper']['ndbc'] = array(
    '#type' => 'fieldset',
    '#title' => t('NDBC Station Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  
  // Get a list of placeholder tokens.
  $tokens = implode(', ', $provider['feeds']['tidal']['tokens']);
  
  $form['wrapper']['ndbc']['meteologic_ndbc_obs_path'] = array(
      '#title' => t('Path'),
      '#description' => t('Alter the path for the NDBC Station feed. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_ndbc_obs_path'),
      '#size' => 120,
      '#required' => TRUE,
  );
  
  $stations = call_user_func($provider['feeds']['tidal']['stations']);
  
  $form['wrapper']['ndbc']['meteologic_ndbc_tidal_station'] = array(
      '#title' => t('NDBC Bouy ID'),
      '#description' => t(''),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_ndbc_tidal_station'),
  );

  return system_settings_form($form);
}