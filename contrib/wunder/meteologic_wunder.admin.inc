<?php
/**
 * @file
 * Meteologic Wunderground settings pages.
 */

/**
 * Form callback.
 * Display settings form for Meteologic Wunderground.
 */
function meteologic_wunder_settings_form() {
  $form = array();

    // Grab provider info.
  $provider = meteologic_providers('wunder');

  $form['wrapper'] = array(
    '#type' => 'fieldset',
    '#description' => t('Each feed currently available in the Wunderground provider is listed below.<br />This module currently uses the following format for Wunderground feeds <br /> http://api.wunderground.com/api/[@apikey]/[feature]/pws:1/q/[@query].xml<br />
    Im most cases the \'pws:1\' flag instructs the api to garner weather data from the nearest \'<b>P</b>ersonal <b>W</b>eather <b>S</b>tation\' to latitude and longitude coordinates defined in the  <b>location::query</b> submitted below.<br />
    See <a target=_blank" href="http://www.wunderground.com/weather/api/d/docs">Wunderground API Docs</a> for more info on this awesome service. You should never need to change the path structure below but it is available as form input here if you need to.'),   
    '#title' => t('Wunderground Settings'),
    '#collapsible' => FALSE,
  );

  $form['wrapper']['meteologic_wunder_apikey'] = array(
      '#title' => t('Wunderground API Key'),
      '#description' => t(''),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_apikey'),
      '#size' => 100,
  );
  
  
  // Get a list of placeholder tokens.
  $tokens = implode(', ', $provider['feeds']['current']['tokens']);
  //current
  $form['wrapper']['meteologic_wunder_current_path'] = array(
      '#title' => t('Current Conditions Path'),
      '#description' => t('Alter the path for the Wunderground Conditions feed. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_current_path'),
      '#size' => 240,
      '#required' => TRUE,
  );
  
  $form['wrapper']['meteologic_wunder_current_apikey'] = array(
      '#type' => 'hidden',
      '#value' => variable_get_value('meteologic_wunder_apikey',''),
  );
  
  $form['wrapper']['meteologic_wunder_current_query'] = array(
      '#type' => 'hidden',
      '#value' => variable_get_value('meteologic_wunder_query',''),
  );
  
  //forecast
  $form['wrapper']['meteologic_wunder_forecast_path'] = array(
      '#title' => t('Forecast Path'),
      '#description' => t('Alter the path for the Wunderground Forecast feed. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_forecast_path'),
      '#size' => 240,
      '#required' => TRUE,
  );

  $form['wrapper']['meteologic_wunder_forecast_apikey'] = array(
      '#type' => 'hidden',
      '#value' => variable_get_value('meteologic_wunder_apikey',''),
  );
  
  $form['wrapper']['meteologic_wunder_forecast_query'] = array(
      '#type' => 'hidden',
      '#value' => variable_get_value('meteologic_wunder_query',''),
  );
  
  

  
  
  
  //tidal
  $form['wrapper']['meteologic_wunder_tidal_path'] = array(
      '#title' => t('Tidal Path'),
      '#description' => t('Alter the path for the Wunderground Tidal feed. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_tidal_path'),
      '#size' => 240,
      '#required' => TRUE,
  );
  
  $form['wrapper']['meteologic_wunder_tidal_apikey'] = array(
      '#type' => 'hidden',
      '#value' => variable_get_value('meteologic_wunder_apikey',''),
  );
  
  $form['wrapper']['meteologic_wunder_tidal_query'] = array(
      '#type' => 'hidden',
      '#value' => variable_get_value('meteologic_wunder_query',''),
  );
  
  
/*
 * DEV Note regarding wunderground features: Although we ended up using paths for current and forecast with the feature hardcoded
 * wunderground does allow the groupig of features into single request. We may want to implement this
 * down the road
 */
  
  $feature_options = array(
      'alerts'=>'alerts', //Returns the short name description, expiration time and a long text description of a severe alert Ñ if one has been issued for the searched upon location.
      'almanac'=>'almanac', //Historical average temperature for today
      'astronomy'=>'astronomy', //Returns the moon phase, sunrise and sunset times.
      'conditions'=>'conditions', //Returns the current temperature, weather condition, humidity, wind, 'feels like' temperature, barometric pressure, and visibility.
      'currenthurricane'=>'currenthurricane', //Returns the current position, forecast, and track of all current hurricanes.
      'forecast'=>'forecast', //Returns a summary of the weather for the next 3 days. This includes high and low temperatures, a string text forecast and the conditions.
      'forecast10day'=>'forecast10day', //Returns a summary of the weather for the next 10 days. This includes high and low temperatures, a string text forecast and the conditions.
      'geolookup'=>'geolookup', //Returns the the city name, zip code / postal code, latitude-longitude coordinates and nearby personal weather stations.
      'history'=>'history', //history_YYYYMMDD returns a summary of the observed weather for the specified date.
      'hourly'=>'hourly', //Returns an hourly forecast for the next 36 hours immediately following the API request.
      'hourly10day'=>'hourly10day', //Returns an hourly forecast for the next 10 days
      'planner'=>'planner', //planner_MMDDMMDD returns a weather summary based on historical information between the specified dates (30 days max).
      'rawtide'=>'rawtide', //Raw Tidal information for graphs
      'tide'=>'tide', //Tidal information
      'webcams'=>'webcams', //Returns locations of nearby Personal Weather Stations and URL's for images from their web cams.
      'yesterday'=>'yesterday'
 );
  /*
  $form['wrapper']['meteologic_wunder_features'] = array(
      '#title' => t('Features'),
      '#description' => t(''),
      '#type' => 'checkboxes',
      '#default_value' => variable_get_value('meteologic_wunder_features'),
      '#options' => $feature_options,
      '#multiple' => TRUE,
      '#size' => count($feature_options),
  );
  */

  
  $form['wrapper']['meteologic_wunder_query_docu'] = array(
      '#markup' => '<span style="font-size:smaller;">The Wunderground provider module is multi-location enabled.<br />Locations are enter below one per line in the form [location name]::[lat,lon]<br /> E.g. el-jebel::39.39498,-107.0903<br /> Only use letter or numerical characters, hypens and underscores for the location part. the query component is comprised of a simple lat,lon string.<br />For each location::query added the module will automatically provide the corresponding blocks.</span>',
  );
  $form['wrapper']['meteologic_wunder_query'] = array(
      '#title' => t('Location::Query'),
      '#type' => 'textarea',
      '#default_value' => variable_get_value('meteologic_wunder_query'),
      '#cols' => 60,
      '#rows' => 5,
  );
  
  
  $form['wrapper']['meteologic_wunder_radar'] = array(
      '#type' => 'fieldset',
      '#title' => t('Wunderground Radar Settings'),
      '#collapsible' => FALSE,
  );
  
 
  $form['wrapper']['meteologic_wunder_radar']['meteologic_wunder_radar_path'] = array(
      '#title' => t('Radar Path'),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_radar_path'),
      '#size' => 240,
      '#maxlength' => 168,
      '#required' => TRUE,
  );
  
  $form['wrapper']['meteologic_wunder_radar_apikey'] = array(
      '#type' => 'hidden',
      '#value' => variable_get_value('meteologic_wunder_apikey',''),
  );
  
  $form['wrapper']['meteologic_wunder_radar']['meteologic_wunder_radar_clat'] = array(
      '#title' => t('Radar Center Latitude'),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_radar_clat'),
      '#size' => 10,
      '#required' => TRUE,
  );
  
  $form['wrapper']['meteologic_wunder_radar']['meteologic_wunder_radar_clon'] = array(
      '#title' => t('Radar Center Longitude'),
    
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_radar_clon'),
      '#size' => 10,
      '#required' => TRUE,
  );
 
  $form['wrapper']['meteologic_wunder_radar']['meteologic_wunder_radar_radius'] = array(
      '#title' => t('Radar Radius'),
     
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_radar_radius', array('default'=>100)),
      '#size' => 10,
      '#required' => TRUE,
  );
 
  $form['wrapper']['meteologic_wunder_radar']['meteologic_wunder_radar_height'] = array(
      '#title' => t('Radar Image Height'),
     
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_radar_height', array('default'=>400)),
      '#size' => 20,
      '#required' => TRUE,
  );
    
  $form['wrapper']['meteologic_wunder_radar']['meteologic_wunder_radar_width'] = array(
      '#title' => t('Radar Image Width'),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_wunder_radar_width', array('default'=>400)),
      '#size' => 20,
      '#required' => TRUE,
  );
  
 
  
  $form['#submit'][] = 'meteologic_wunder_settings_custom_submit';
  return system_settings_form($form);
}



function meteologic_wunder_settings_custom_submit($form, &$form_state) {

  if(isset($form_state['values']['meteologic_wunder_apikey'])){
    if(!isset($form_state['values']['meteologic_wunder_current_apikey'])){
      $form_state['values']['meteologic_wunder_current_apikey'] = $form_state['values']['meteologic_wunder_apikey'];
    }
    if(!isset($form_state['values']['meteologic_wunder_forecast_apikey'])){
      $form_state['values']['meteologic_wunder_forecast_apikey'] = $form_state['values']['meteologic_wunder_apikey'];
    }
    if(!isset($form_state['values']['meteologic_wunder_tidal_apikey'])){
      $form_state['values']['meteologic_wunder_tidal_apikey'] = $form_state['values']['meteologic_wunder_apikey'];
    }
    
    if(!isset($form_state['values']['meteologic_wunder_radar_apikey'])){
      $form_state['values']['meteologic_wunder_radar_apikey'] = $form_state['values']['meteologic_wunder_apikey'];
    }
    
  }
  
  if(isset($form_state['values']['meteologic_wunder_query'])){
    if(!isset($form_state['values']['meteologic_wunder_current_query']) || $form_state['values']['meteologic_wunder_current_query'] != $form_state['values']['meteologic_wunder_query']){
      $form_state['values']['meteologic_wunder_current_query'] = $form_state['values']['meteologic_wunder_query'];
    }
    if(!isset($form_state['values']['meteologic_wunder_forecast_query'])|| $form_state['values']['meteologic_wunder_forecast_query'] != $form_state['values']['meteologic_wunder_query']){
      $form_state['values']['meteologic_wunder_forecast_query'] = $form_state['values']['meteologic_wunder_query'];
    }
    if(!isset($form_state['values']['meteologic_wunder_tidal_query']) || $form_state['values']['meteologic_wunder_tidal_query'] != $form_state['values']['meteologic_wunder_query']){
      $form_state['values']['meteologic_wunder_tidal_query'] = $form_state['values']['meteologic_wunder_query'];
    }
  }

}
