<?php
/**
 * @file
 * Meteologic Wunderground theme functions.
 *
 * NOTE: These theme functions *must* live in this file, named exactly like this.
 * We enforce convention over configuration in order to make things simpler
 * for submodules so theme callbacks must always live in "MODULENAME.theme.inc",
 * located in the module's root.
 */

/**
 * Provides a theme for theme Wunderground Current feed.
 * @return rendered table of all available data retrieved from wunderground current conditions
 */
function theme_meteologic_wunder_current($variables) {

  
  drupal_add_css(drupal_get_path('module', 'meteologic_wunder') . '/css/meteologic-wunder.css', array('group' => CSS_DEFAULT));
  if(!$variables['data']['current_observation']){
    $output = '';
    }else{
    $current = $variables['data']['current_observation'];

    $output = '<div id="current-wrapper">';
    $output .= '<div id="current-conditions">';
    $output .= '<div id="current-image">';
    $output .= '<img src="'.$current['icon_url'].'">';
    $output .= '</div>';
    $output .= '<div id="current-temp">';
    $output .= $current['weather'].'<br />';
    $output .= '<span class="temp">'.$current['temperature_string'].'</span>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '<div id="current-data">';
    $output .= '<div class="current-data-item">';
    $output .= '<label>Humidity:</label><div>'.$current['relative_humidity'].'</div>';
    $output .= '</div>';
    $output .= '<div class="current-data-item">';
    $output .= '<label>Dewpoint:</label><div>'.$current['dewpoint_string'].'</div>';
    $output .= '</div>';
    $output .= '<div class="current-data-item">';
    $output .= '<label>Visibility:</label><div>'.$current['visibility_mi'].' mi.</div>';
    $output .= '</div>';
    $output .= '<div class="current-data-item">';
    $output .= '<label>Barometer:</label><div>'.$current['pressure_in'].'"</div>';
    $output .= '</div>';
    $output .= '<div class="current-data-item">';
    $output .= '<label>Wind:</label><div>'.$current['wind_string'].'</div>';
    $output .= '</div>';
    $output .= '</div>';
    $output .= '</div>';
  }
    return $output;
}


function theme_meteologic_wunder_forecast($variables) {

  drupal_add_css(drupal_get_path('module', 'meteologic_wunder') . '/css/meteologic-wunder.css', array('group' => CSS_DEFAULT));
  
  if(!$variables['data']['forecast']){
    $forecast_output = '';
  }else{
    $forecastdays = $variables['data']['forecast']['simpleforecast']['forecastdays']['forecastday'];
    $forecastdayheaders = array(t('Data Type'), t('Value'));
    $forcastheaders = array();
    $i= 0;
    foreach ($forecastdays as $forecastday){
      $forecastdayepoch = $forecastday['date']['epoch'];
      $forecastdayouput[$i]['header'] = date('l',$forecastdayepoch);
      $dayoutput = '';
      $icon = $forecastday['icon_url'];
      $dayoutput .= '<div class="wunder-forecast-icon"><img src="'.$icon.'"></div>';
      $dayoutput .= '<div class="wunder-forecast-data"><span class="temp-hi">'.$forecastday['high']['fahrenheit'].'</span>/<span class="temp-lo">'.$forecastday['low']['fahrenheit'].'</span></div>';
      $forecastdayouput[$i]['dayoutput'] =  $dayoutput;
      $i++;
    }
    $forecast_output = '';
    foreach ($forecastdayouput as $value) {
      $forecast_output .= '<div class="meteologic-forecastday">';
      $forecast_output .= '<div class="meteologic-forecastday-header">'.$value['header'].'</div>';
      $forecast_output .= '<div class="meteologic-forecastday-default-display">';
      $forecast_output .= $value['dayoutput'];
      $forecast_output .= '</div>';
      $forecast_output .= '</div>';
    }
  }
  return '<div class="meteologic-forecast-wrapper">'.$forecast_output.'</div>';
}


function theme_meteologic_wunder_tidal($variables) {
  kpr($variables);
  $tides = $variables['data']['tide']['tideSummary']['observation'];
  //$rows = array();
  foreach ($tides as $tide){
    $type = $tide['data']['type'];
    $date = $tide['date']['pretty'];
    $height = $tide['data']['height'];
    if($date && $type && $height){
    $rows[] = array($type,$date,$height);
    }
  }
 $headers = array(t('Type'), t('Date/Time'), t('Height'));
  return theme('table', array('header' => $headers, 'rows' => $rows));
}

/**
 * Provides a theme for them NOAA Current Conditions feed.
 */
function theme_meteologic_wunder_radar($variables) {
  $base_path = 'sites/default/files/meteologic/wunder/radar/current_radar.gif?cb='.rand();
  // @TODO do something with these results.
  $radar_display ='<div id="meteologic-noaa-radar-map"><img src="'.$base_path.'"></div><br clear="all" />';
  return $radar_display;
}

