<?php
/**
 * @file
 * Meteologic NOAA theme functions.
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
  $data = $variables['data'];
  $rows = array();

  // Last Updated.
  $rows[] = array(
    t('Last Updated'),
    $data['observation_time']
  );

  // Weather.
  $rows[] = array(
    t('Weather'),
    $data['weather']
  );

  // Temperature.
  $rows[] = array(
    t('Temperature'),
    "{$data['temp_f']} &deg;F ({$data['temp_c']} &deg;C)",
  );

  // Dewpoint.
  $rows[] = array(
    t('Dewpoint'),
    "{$data['dewpoint_f']} &deg;F ({$data['dewpoint_c']} &deg;C)",
  );

  // Relative Humidity.
  $rows[] = array(
    t('Relative Humidity'),
    "{$data['relative_humidity']} %",
  );

  // Relative Humidity.
  $rows[] = array(
    t('Visibility'),
    "{$data['visibility_mi']} miles",
  );

  // MSL Pressure.
  $rows[] = array(
    t('MSL Pressure'),
    "{$data['pressure_mb']} mb",
  );

  // Altimeter.
  $rows[] = array(
    t('Altimeter'),
    "{$data['pressure_in']} in Hg",
  );

  return theme('table', array('header' => array(), 'rows' => $rows));
}