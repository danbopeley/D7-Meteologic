<?php
/**
 * @file
 * Meteologic theme functions.
 */

/**
 * Theme callback.
 *
 * Renders draggble table in Meteologic feed settings form.
 *
 * @see meteologic_theme()
 */
function theme_meteologic_form_feed_config($variables) {
  $form = $variables['form'];

  if (!isset($form['enabled']['empty'])) {
    $table_id = 'meteologic-feed-providers-table';
    $class = 'meteologic-provider-weight';
    $header = array(t('Name'), t('Weight'));
    $rows = array();

    foreach (element_children($form['order']['providers']) as $id) {
      $form['order']['providers'][$id]['weight']['#attributes']['class'] = array($class);
      $rows[] = array(
        'data' => array(
          drupal_render($form['order']['providers'][$id]['name']),
          drupal_render($form['order']['providers'][$id]['weight']),
        ),
        'class' => array('draggable'),
      );
    }

    $form['order']['providers']['table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#attributes' => array('id' => $table_id),
    );

    drupal_add_tabledrag($table_id, 'order', 'sibling', $class);
  }

  $output = drupal_render_children($form);
  return $output;
}

/**
 * Theme callback.
 * Provides a default theme implementation for the Current Conditions feed.
 *
 * @see meteologic_theme()
 */
function theme_meteologic_default_current($variables) {
  $data = $variables['data'];
  $rows = array();

  // @TODO make sure these keys are global.

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