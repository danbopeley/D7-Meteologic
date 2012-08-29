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
        ),
      ),
      // Stations callback.
      'stations' => array(

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