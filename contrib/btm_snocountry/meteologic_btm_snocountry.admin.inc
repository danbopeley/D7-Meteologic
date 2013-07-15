<?php
/**
 * @file
 * Meteologic btm_snocountryground settings pages.
 */

/**
 * Form callback.
 * Display settings form for Meteologic btm_snocountryground.
 */
function meteologic_btm_snocountry_settings_form() {
  $form = array();

    // Grab provider info.
  $provider = meteologic_providers('btm_snocountry');

  $form['wrapper'] = array(
    '#type' => 'fieldset',
    '#description' => t('Each feed currently available in the btm_snocountryground provider is listed below.<br />This module currently uses the following format for btm_snocountryground feeds <br /> http://api.btm_snocountryground.com/api/[@apikey]/[feature]/pws:1/q/[@query].xml<br />
    Im most cases the \'pws:1\' flag instructs the api to garner weather data from the nearest \'<b>P</b>ersonal <b>W</b>eather <b>S</b>tation\' to latitude and longitude coordinates defined in the  <b>location::query</b> submitted below.<br />
    See <a target=_blank" href="http://www.btm_snocountryground.com/weather/api/d/docs">btm_snocountryground API Docs</a> for more info on this awesome service. You should never need to change the path structure below but it is available as form input here if you need to.'),   
    '#title' => t('BTM Snocountry Settings'),
    '#collapsible' => FALSE,
  );


  // Get a list of placeholder tokens.
  $tokens = implode(', ', $provider['feeds']['snow']['tokens']);
  //current
  $form['wrapper']['meteologic_btm_snocountry_path'] = array(
      '#title' => t('BTM Snocountry Feed Path'),
      '#description' => t('Alter the path for the BTM Snocountry Report feed. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_btm_snocountry_path'),
      '#size' => 240,
      '#required' => FALSE,
  );
  $form['wrapper']['meteologic_btm_snocountry_snow_days'] = array(
      '#title' => t('BTM Snocountry Days'),
      '#description' => t('Number of days to historical report'),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_btm_snocountry_snow_days'),
      '#size' => 10,
  );
  
  $form['wrapper']['meteologic_btm_snocountry_query_docu'] = array(
      '#markup' => '<span style="font-size:smaller;">The BTM Snocountry provider module is multi-location enabled.<br />Locations are enter below one per line in the form [location name]::[lat,lon]<br /> E.g. el-jebel::39.39498,-107.0903<br /> Only use letter or numerical characters, hypens and underscores for the location part. the query component is comprised of a simple lat,lon string.<br />For each location::query added the module will automatically provide the corresponding blocks.</span>',
  );
  
  $form['wrapper']['meteologic_btm_snocountry_snow_query'] = array(
      '#title' => t('Location::ResortID'),
      '#type' => 'textarea',
      '#default_value' => variable_get_value('meteologic_btm_snocountry_snow_query'),
      '#cols' => 60,
      '#rows' => 5,
  );
  
  $form['wrapper']['meteologic_btm_snocountry_offseason'] = array(
      '#title' => t('Off Season Message'),
      '#type' => 'textarea',
      '#default_value' => variable_get_value('meteologic_btm_snocountry_offseason'),
      '#cols' => 60,
      '#rows' => 5,
  );
  
  $form['wrapper']['meteologic_btm_snocountry_disable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Disable Snow Report'),
      '#description' => t('Check this box to disable the snowreport. If checked snowreport feeds will be disabled and the main snow report will display the offseason message if one exists.'),
      '#default_value' => variable_get('meteologic_btm_snocountry_disable', FALSE),
  );
  
  $form['wrapper']['meteologic_btm_snocountry_hide'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide Snow Report'),
      '#description' => t('Check this box to hide the snowreport where ever it appears.'),
      '#default_value' => variable_get('meteologic_btm_snocountry_hide', FALSE),
  );
  
  
  
  //$form['#submit'][] = 'meteologic_btm_snocountry_settings_custom_submit';
  return system_settings_form($form);
}



function meteologic_btm_snocountry_settings_custom_submit($form, &$form_state) {



}
