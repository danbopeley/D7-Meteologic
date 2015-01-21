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
function theme_meteologic_mesowest_current($variables) {
  $data = $variables['data'];

  $rows = array();

  // Last Updated.
  $rows[] = array(
    t('Last Updated'),
    $data['cd']['observation_time']
  );

  // Temperature.
  $rows[] = array(
    t('Temperature'),
    "{$data['cd']['temp_f']} &deg;F ({$data['cd']['temp_c']} &deg;C)",
  );

  // Dewpoint.
  $rows[] = array(
    t('Dewpoint'),
    "{$data['cd']['dewpoint_f']} &deg;F ({$data['cd']['dewpoint_c']} &deg;C)",
  );

  // Relative Humidity.
  $rows[] = array(
    t('Relative Humidity'),
    "{$data['cd']['relative_humidity']} %",
  );

  // Relative Humidity.
  $rows[] = array(
    t('Visibility'),
    "{$data['cd']['visibility_mi']} miles",
  );

  // MSL Pressure.
  $rows[] = array(
    t('MSL Pressure'),
    "{$data['cd']['pressure_mb']} mb",
  );

  // Altimeter.
  $rows[] = array(
    t('Altimeter'),
    "{$data['cd']['pressure_in']} in Hg",
  );

  return theme('table', array('header' => array(), 'rows' => $rows));
}