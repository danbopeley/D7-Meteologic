<?php
/**
 * @file
 * Meteologic btm_snocountryground theme functions.
 *
 * NOTE: These theme functions *must* live in this file, named exactly like this.
 * We enforce convention over configuration in order to make things simpler
 * for submodules so theme callbacks must always live in "MODULENAME.theme.inc",
 * located in the module's root.
 */

/**
 * Provides a theme for theme btm_snocountryground Current feed.
 * @return rendered table of all available data retrieved from btm_snocountryground current conditions
 */
function theme_meteologic_btm_snocountry($variables) {

  $disabled = variable_get('meteologic_btm_snocountry_disable', FALSE);
  $hide = variable_get('meteologic_btm_snocountry_hide', FALSE);
  $status = $variables['data']['report']['operatingStatus'];
 
  if($hide){
    return;
  }

  
  drupal_add_css(drupal_get_path('module', 'meteologic_btm_snocountry') . '/css/meteologic-btm-snocountry.css', array('group' => CSS_DEFAULT));
  if($disabled){
    $offseason = variable_get_value('meteologic_btm_snocountry_offseason');
    if($offseason){
      $output = '<div id="skireport-wrapper">';
      $output .= $offseason;
      $output .= '</div>';
    }else{
      $output = '<div id="skireport-wrapper">';
      $output .= $status;
      $output .= '</div>';
    }
    
    return $output;
  }
  if(!$variables['data']['report']){
    $output = 'No Report available';
    }else{
    $report = $variables['data']['report'];
    
    if($report['newSnowMax'] && $report['newSnowMax'] > $report['newSnowMin']){
        $newsnow = $report['newSnowMax'];
    }else if($report['newSnowMin'] && $report['newSnowMin'] > $report['newSnowMax'] ){
      $newsnow = $report['newSnowMin']; 
    }else if ($report['newSnowMax'] == $report['newSnowMin']){
      $newsnow = $report['newSnowMax'];
    }
    
    if($report['avgBaseDepthMax'] && $report['avgBaseDepthMax'] > $report['avgBaseDepthMin']){
      $basedepth = $report['avgBaseDepthMax'];
    }else if($report['avgBaseDepthMin'] && $report['avgBaseDepthMin'] > $report['avgBaseDepthMax'] ){
      $basedepth = $report['avgBaseDepthMin'];
    
    }else if ($report['avgBaseDepthMax'] == $report['avgBaseDepthMin']){
      $basedepth= $report['avgBaseDepthMax'];
    }
    
    
    $lastupdate = date('l M jS Y h:i a', $report['ts']);
    $output = '<div id="skireport-wrapper">';
    
      $output .= '<div id="skireport-heading">';
        $output .= '<div class="skireport-resort-name">'.$report['resortName'].'</div>';
        $output .= '<div class="skireport-last-updated">Updated on '.$lastupdate.'</div>';
        $output .= '<div class="skireport-status">'.$report['operatingStatus'].'</div>';
      $output .= '</div>';

      $output .= '<div id="skireport-conditions">';
      //$output .= '<div id="skireport-image">';
     // $output .= '<img src="'.$report['icon_url'].'">';
      //$output .= '</div>';
        $output .= '<div id="skireport-newsnow">';
        $output .= '<span class="newsnow">'.$newsnow.'</span>" in last 24 hours';
        $output .= '</div>';
        $output .= '<div id="skireport-basedepth">';
        $output .= '<span class="basedepth">'.$basedepth.'</span>"';
        $output .= '</div>';
      $output .= '</div>';
      
      $output .= '<div id="skireport-data">';
        $output .= '<div class="skireport-data-item">';
        $output .= '<label>Open Trails: </label><div>'.$report['openDownHillTrails'].'</div>';
        $output .= '</div>';
        $output .= '<div class="skireport-data-item">';
        $output .= '<label>Open Lifts: </label><div>'.$report['openDownHillLifts'].'</div>';
        $output .= '</div>';
        $output .= '<div class="skireport-data-item">';
        $output .= '<label>Total Open Area: </label><div>'.$report['openDownHillAcres'].' acres ('.$report['openDownHillPercent'].'%)</div>';
        $output .= '</div>';
      $output .= '</div>';
    $output .= '</div>';
  }
    return $output;
}






