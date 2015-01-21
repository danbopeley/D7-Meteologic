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

    $output = '<div class="current-wrapper">';
    $output .= '<div class="current-conditions">';
    $output .= '<div class="current-image">';
    $output .= '<img src="'.$current['icon_url'].'">';
    $output .= '</div>';
    $output .= '<div class="current-data">';
    $output .= '<div class="current-temp">';
    $output .= '<div class="current-weather">'.$current['weather'].'</div>';

    $output .= '<span class="temp">'.$current['temperature_string'].'</span>';
    $output .= '</div>';
    $output .= '<div class="current-data-item">';
    $output .= '<label>Humidity:</label><div>'.$current['relative_humidity'].'</div>';
    $output .= '</div>';
    $output .= '<div class="current-data-item">';
    $output .= '<label>Dew Point:</label><div>'.$current['dewpoint_string'].'</div>';
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
 * Provides a theme for theme for Wunder Radar pic.
 */
function theme_meteologic_wunder_radar($variables) {
  $fid = db_select("file_managed", "fm")
    ->fields("fm", array("fid"))
    ->condition("uri", "public://meteologic/wunder/radar/current_radar.gif")
    ->execute()
    ->fetchField();
  $radar = file_load($fid);
  $variables= array(
    'path' => $radar->uri,
    'alt' => 'Current Radar',
    'title' => 'Current Radar',
    'attributes' => array('class' => 'current-radar'),
  );
  $radar_image = theme('image', $variables);
  $radar_display ='<div id="meteologic-noaa-radar-map">'.$radar_image.'</div><br clear="all" />';
  return $radar_display;
}
