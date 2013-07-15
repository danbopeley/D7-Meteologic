<?php
/**
 * @file
 * Meteologic NOAA theme functions.
 */

/**
 * Theme callback.
 * Provides a theme for Current Conditions.
 *
 * @see meteologic_noaa_theme()
 *
 * NOTE: These theme functions *must* live in this file, named exactly like this.
 * We enforce convention over configuration in order to make things simpler
 * for submodules so theme callbacks must always live in "MODULENAME.theme.inc",
 * located in the module's root.
 */

/**
 * Provides a theme for them NOAA Current Conditions feed.
 */
function theme_meteologic_noaa_current($variables) {
  kpr($variables);
      $cur= $variables;
      $cur_image = '<img class="scalable" src="'.$cur['icon_url_base'].$cur['icon_url_name'] .'" />';
      $display_out = '<div class="current">';
      $display_out .= '<div class="current-image">';
      $display_out .= $cur_image;
      $display_out .= '</div>';
      $display_out .= '<div class="current-data">';
      $display_out .= $cur['weather'].'<br />';
      $display_out .= '<span class="temp-far">'.$cur['temp_f'].'&deg;F</span><span class="temp-cel">('.$cur['temp_c'].'&deg;C)</span>';
      $display_out .= '</div>';
      $display_out .= '</div>';
      
      return '';
}

/**
 * Provides a theme for them NOAA Current Conditions feed.
 */
function theme_meteologic_noaa_forecast($variables) {
  //kpr($variables);
  $data = $variables['data']['data'];

$display_out = '<div class="forecast-wrapper">';
for ($i = 0; $i < 5; $i++) {
      $dayindex = $i * 2;
      $nightindex =  $dayindex + 1;    
      $daystamp = strtotime($data['time-layout'][0]['start-valid-time'][$i]);
      $dow = date('l',$daystamp);
      $forecast_icon1 = $data['parameters']['conditions-icon']['icon-link'][$dayindex];
      $forecast_icon2 = $data['parameters']['conditions-icon']['icon-link'][$nightindex];
      $hi = $data['parameters']['temperature'][0]['value'][$i];
      $lo = $data['parameters']['temperature'][1]['value'][$i];
      $pop1 = $data['parameters']['probability-of-precipitation']['value'][$dayindex];
      $pop2 = $data['parameters']['probability-of-precipitation']['value'][$nightindex];
      $weather1 = $data['parameters']['weather']['weather-conditions'][$dayindex]['@attributes']['weather-summary'];
      $weather2 = $data['parameters']['weather']['weather-conditions'][$nightindex]['@attributes']['weather-summary'];;
      if($i == 0 && is_array($forecast_icon1)){
        $forecast_icon1 = $forecast_icon2;
        $dow = 'Tonight';
      }
      $display_out .= '<div class="forecast-day-wrapper">';
      $display_out .= '<div class="forecast-day-inner">';
      $display_out .= '<div class="forecast-day-heading">'.$dow.'</div>';
      $display_out .= '<div class="forecast-day-icon"><img class="scalable" width="55" height="58" src="'.$forecast_icon1.'"></div>';
      $display_out .= '<div class="forecast-day-weather">'.$weather1.'</div>';
      $display_out .= '<div class="forecast-day-hilo">HI:'.$hi.' / LO:'.$lo.'</div>';
      $display_out .= '<div class="forecast-day-pop">Probablilty of Precipitation: '.$pop1.'%</div>';
      $display_out .= '</div>';
      $display_out .= '</div>';

}
$display_out .= '</div>';
  // @TODO do something with these results.
return $display_out;
}


/**
 * Provides a theme for them NOAA Current Conditions feed.
 */
function theme_meteologic_noaa_radar($variables) {
  
  $radar_station = $variables['data'][0];
  $radar_station = 'HMO';
  $base_path = 'sites/default/files/meteologic/noaa/radar/'.$radar_station.'/';
  // @TODO do something with these results.
  drupal_add_css(NOAA_MODULE_PATH .'/css/meteologic-noaa-styles.css', 'module', 'all');
  $radar_display ='<div id="meteologic-noaa-radar-map">
  <div id="radar-map-0" class="radar-map"><img src="'.$base_path.'Topo_Short.jpg" alt="" /></div>
  <div id="radar-map-1" class="radar-map"><img src="'.$base_path.'current_radar.gif" name="conditionalimage" alt="" /></div>
  <div id="radar-map-2" class="radar-map"><img src="'.$base_path.'County_Short.gif" alt="" /></div>
  <div id="radar-map-3" class="radar-map"><img src="'.$base_path.'Rivers_Short.gif" alt="" /></div>
  <div id="radar-map-4" class="radar-map"><img src="'.$base_path.'Highways_Short.gif" alt="" /></div>
  <div id="radar-map-5" class="radar-map"><img src="'.$base_path.'City_Short.gif" alt="" /></div>
  <div id="radar-map-6" class="radar-map"><img src="'.$base_path.'current_legend.gif" alt="" /></div>
  <br clear="all" />
</div><br clear="all" />';

  
  return $radar_display;

}
