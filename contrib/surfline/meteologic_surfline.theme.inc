<?php
/**
 * @file
 * Meteologic MesoWest theme functions.
 *
 * NOTE: These theme functions *must* live in this file, named exactly like this.
 * We enforce convention over configuration in order to make things simpler
 * for submodules so theme callbacks must always live in "MODULENAME.theme.inc",
 * located in the module's root.
 */

/**
 * Provides a theme for Surfline feed.
 */
function theme_meteologic_surfline_report($variables) {

  $data = $variables['data'];
  $rows = array();
  $surfline_output = '';
  foreach ($data['surf'] as $i => $value) {
   // $surfline_output .= '<div class="surfline-report">'.$value['title'].'<br>'.str_replace('This is LOLA with the forecast for ','',$value['description']).'</div>';
    $surfline_output .= '<div class="surfline-report">'.$value['title'].'<br><span style="font-size:smaller;">'.$value['description'].'</span></div>';
   // $surfline_output .= '<div class="surfline-report">'.str_replace('This is LOLA with the forecast for ','',$value['description']).'</div>';
    
    $rows[] = array(
        $value['title'],
    );
  }
  return '<div class="meteologic-surfline-wrapper"><div>provided by <a target="_blank" href="http:/www.surfline.com">Surfline.com</a></div>'.$surfline_output.'</div>';
 
}