<?php
/**
 * @file
 * Meteologic Surfline settings pages.
 */

/**
 * Form callback.
 * Display settings form for Meteologic Surfline.
 */
function meteologic_surfline_settings_form() {
  $form = array();

    // Grab provider info.
  $provider = meteologic_providers('surfline');

  $form['wrapper'] = array(
    '#type' => 'fieldset',
    '#title' => t('Surfline'),
    '#collapsible' => FALSE,
  );

  // Current conditions feed settings.
  $form['wrapper']['surfline'] = array(
    '#type' => 'fieldset',
    '#title' => t('Surfline Feed Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  
  // Get a list of placeholder tokens.
  $tokens = implode(', ', $provider['feeds']['surf']['tokens']);
  
  $form['wrapper']['surfline']['meteologic_surfline_feed_path'] = array(
      '#title' => t('Path'),
      '#description' => t('Alter the path for the Surfline feed. You may use the following placeholder tokens: @tokens', array('@tokens' => $tokens)),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_surfline_feed_path'),
      '#size' => 120,
      '#required' => TRUE,
  );
  
  //$stations = call_user_func($provider['feeds']['surf']['stations']);
  
  $form['wrapper']['surfline']['meteologic_surfline_surf_feedid'] = array(
      '#title' => t('Surfline Feed ID'),
      '#description' => t(''),
      '#type' => 'textfield',
      '#default_value' => variable_get_value('meteologic_surfline_surf_feedid'),
  );

  return system_settings_form($form);
}