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
      // Provider name.
      'name' => t('Foo Provider'),
      // Settings form callback, this is optional but can be useful to allow
      // users to customize placeholder tokens (see below). If used, this file
      // *must* live in a file called "module.admin.inc".
      //
      // For example: "foo_admin.inc".
      'settings' => 'foo_settings_form',
      // An array of feeds implemented, where the key is the feed's slug and
      // the array contains an array with information.
      'feeds' => array(
        // Feed slug.
        'current' => array(
          // Feed path.
          // The path is always available as a variable with the name:
          // "module_feed_path", where "provider" is the slug of
          // the provider.
          //
          // For example: "foo_current_path".
          'path' => 'http://example.com/foo',

          // Feed tokens. These are values that will get replaced by
          // customizable variables in the provider's settings. The
          // corresponding variable name MUST be "module_feed_token",
          // where "provider" is the slug of the provider and "token is the
          // name of the token minus the @.
          //
          // For example, for @station, the variable name will be:
          // "foo_current_station".
          'tokens' => array('@station'),

          // Theme functions.
          // Specify either a single callback function or one for each of pages
          // and blocks.
          //
          // NOTE: You do not have to implement hook_theme() yourself
          // but you DO have to place these callbacks in a file called:
          // "MODULENAME.theme.inc", located in the module's root directory.
          // Note that the callback must be prefixe with "theme_".
          //
          // For example: "theme_foo_current".
          'theme' => 'foo_current',
          // Alternatively, you can specify different theme callbacks for pages
          // and blocks:
//          'theme' => array(
//            'block' => 'foo_current_block',
//            'page' => 'foo_current_page',
//          ),
          // Stations callback.
          // Specify a callback function that will be used to load a list of
          // stations for this provider's feed.
          'stations' => 'foo_stations_current',
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