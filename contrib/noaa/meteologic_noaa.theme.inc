<?php
/**
 * @file
 * Meteologic NOAA theme functions.
 */

/**
 * Theme callback.
 * Provides a theme implementation for the the Current Conditions feed.
 *
 * @see meteologic_noaa_theme()
 */
function theme_meteologic_noaa_current_block($variables) {
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