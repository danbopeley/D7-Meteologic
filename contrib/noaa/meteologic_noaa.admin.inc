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

  // Grab provider info.
  $provider = meteologic_providers('noaa');

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
  $tokens = implode(', ', $provider['feeds']['current']['tokens']);

  $form['wrapper']['current']['meteologic_noaa_current_path'] = array(
    '#title' => t('Path'),
    '#description' => t('Alter the path for the NOAA Current Conditions feed. It does not happen often, but in the event the base path to this feed changes you may reset it here. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
    '#type' => 'textfield',
    '#default_value' => variable_get_value('meteologic_noaa_current_path'),
    '#size' => 120,
    '#maxlength' => 240,
    '#required' => TRUE,
  );

  $stations = call_user_func($provider['feeds']['current']['stations']);

  $form['wrapper']['current']['meteologic_noaa_current_station'] = array(
    '#title' => t('Station'),
    '#description' => t(''),
    '#type' => 'select',
    '#options' => $stations,
    '#default_value' => variable_get_value('meteologic_noaa_current_station'),
  );

  // Point forecast feed settings.
  $form['wrapper']['forecast'] = array(
    '#type' => 'fieldset',
    '#title' => t('Point Forecast'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Get a list of placeholder tokens.
  $tokens = implode(', ', $provider['feeds']['forecast']['tokens']);

  $form['wrapper']['forecast']['meteologic_noaa_forecast_path'] = array(
    '#title' => t('Path'),
    '#description' => t('Alter the path for the NOAA Point Forecast feed. It does not happen often, but in the event the base path to this feed changes you may reset it here. You may use the following placeholder tokens: @tokens .', array('@tokens' => $tokens)),
    '#type' => 'textfield',
    '#default_value' => variable_get_value('meteologic_noaa_forecast_path'),
    '#size' => 120,
    '#maxlength' => 240,
    '#required' => TRUE,
  );

  $form['wrapper']['forecast']['meteologic_noaa_forecast_lat'] = array(
    '#title' => t('Latitude'),
    '#description' => t('Alter the NOAA Point Forecast Latitude.'),
    '#type' => 'textfield',
    '#default_value' => variable_get_value('meteologic_noaa_forecast_lat'),
    '#size' => 10,
    '#required' => TRUE,
  );

  $form['wrapper']['forecast']['meteologic_noaa_forecast_lon'] = array(
    '#title' => t('Longitude'),
    '#description' => t('Alter the NOAA Point Forecast Longitude.'),
    '#type' => 'textfield',
    '#default_value' => variable_get_value('meteologic_noaa_forecast_lon'),
    '#size' => 10,
    '#required' => TRUE,
  );

  $form['wrapper']['forecast']['meteologic_noaa_forecast_days'] = array(
    '#title' => t('Days'),
    '#description' => t('Alter number of Days for the NOAA Point Forecast.'),
    '#type' => 'select',
    '#default_value' => variable_get_value('meteologic_noaa_forecast_days'),
    '#options' => drupal_map_assoc(array(3, 4, 5, 6, 7, 8, 9)),
    '#required' => TRUE,
  );
  
  // Point forecast feed settings.
  $form['wrapper']['radar'] = array(
      '#type' => 'fieldset',
      '#title' => t('Radar Picture'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
  );
  
  $form['wrapper']['radar']['meteologic_noaa_radar_path'] = array(
      '#title' => t('Path'),
      '#description' => t('Alter the base path for the NOAA Radar picture source. It does not happen often, but in the event the base path to this feed changes you may reset it here'),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_noaa_radar_path'),
      '#size' => 120,
      '#maxlength' => 240,
      '#required' => TRUE,
  );
  
  $stations = call_user_func($provider['feeds']['radar']['stations']);
  
  $form['wrapper']['radar']['meteologic_noaa_radar_station'] = array(
      '#title' => t('Radar Station'),
      '#description' => t(''),
      '#type' => 'select',
      '#options' => $stations,
      '#default_value' => variable_get_value('meteologic_noaa_radar_station'),
  );
  $form['#submit'][] = 'meteologic_noaa_settings_custom_submit';
  return system_settings_form($form);
}

function meteologic_noaa_settings_custom_submit($form, &$form_state) {
  
  if(isset($form_state['values']['meteologic_noaa_radar_station'])){
    $cur_radar_station = variable_get_value('meteologic_noaa_radar_station', NULL);
    $radar_station = $form_state['values']['meteologic_noaa_radar_station'];
    if($cur_radar_station != $radar_station){
      $got_station = meteologic_noaa_get_radar_overlays($radar_station);
    }
  }
  
}

