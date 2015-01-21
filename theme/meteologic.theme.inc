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

function meteologic_preprocess_meteologic_homepagewidget(&$vars) {
  
  foreach ($vars['data'] as $key => $value) {
    $vars[$key] = $value;
  }
  $vars['link_to_full'] = l(variable_get('meteologic_details_text', 'Detailed Weather'), variable_get('meteologic_details_path', 'weather'), array());
}
 
function meteologic_preprocess_meteologic_footerwidget(&$vars) {
  foreach ($vars['data'] as $key => $value) {
    $vars[$key] = $value;
  }
  $vars['link_to_full'] = l(variable_get('meteologic_details_text', 'Detailed Weather'), variable_get('meteologic_details_path', 'weather'), array());
}


