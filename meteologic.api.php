<?php
/**
 * @file
 * Meteologic API Documentation.
 */

/**
 * Implements hook_meteologic_provider_info();
 */
function hook_meteologic_provider_info() {
  return array(
    'foo' => array(
      // Name.
      'name' => t('Foo Provider'),
      // Settings form callback.
      'settings' => 'foo_settings_form',
      // Feeds implemented.
      'feeds' => array(
        // Feed slug.
        'current' => array(
          // Feed path.
          'path' => 'http://example.com/foo',
          // Theme functions.
          // Specify a callback function for both themes and blocks. If there's
          // no change just specify the same one twice.
          // 
          // NOTE: You do not have to implement hook_theme() yourself
          // but you DO have to place these callbacks in a file called:
          // "MODULENAME.theme.inc", located in the module's root directory.
          'theme' => array(
            'block' => 'foo_current_block',
            'page' => 'foo_current_page',
          ),
        ),
      ),
      // Stations callback.
      // You most likely just need to implement the "weather" callback.
      // However, some providers have different stations for radar feeds.
      'stations' => array(
        'weather' => 'foo_stations_weather',
        'radar' => 'foo_stations_radar',
      ),
    ),
  );
}

/**
 * Implements hook_meteologic_feed_info().
 */
function hook_meteologic_feed_info() {
  return array(
    'current' => array(
      'name' => t('Current Conditions'),
//      'blocks' => 1,
//      'page' => TRUE,
    ),
  );
}