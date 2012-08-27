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
      'name' => t('Foo Provider'),
      'class' => 'MeteologicFoo',
      'settings' => 'foo_settings_form',
      'feeds' => array(
        'current' => array(
          'path' => 'http://example.com/foo',
        ),
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