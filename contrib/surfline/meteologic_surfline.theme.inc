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

 // kpr($variables);
  
  
  $data = $variables['data'];
  $rows = array();


  foreach ($data['surf'] as $i => $value) {


    $rows[] = array(
        $value['title'],
    );
  }

  return theme('table', array('header' => array(), 'rows' => $rows));
}