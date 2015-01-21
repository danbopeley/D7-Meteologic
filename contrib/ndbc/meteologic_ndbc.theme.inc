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
 * Provides a theme for them MesoWest Current Conditions feed.
 */
function theme_meteologic_ndbc_bouy_obs($variables) {

  $data = $variables['data'];
  $rows = array();
  $rows[] = array(
      t('Latest Observations From '. $data['station'])
  );

  foreach ($data['obs'] as $i => $value) {
    if($i == 0){
      $value = 'Updated on '.$value;
    }

    $rows[] = array(
        $value,
    );
  }

  return theme('table', array('header' => array(), 'rows' => $rows));
}