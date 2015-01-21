<?php
/**
 * @file
 * Meteologic admin pages.
 */

/**
 * Form callback.
 * Displays meteologic global settings form.
 *
 * @see meteologic_menu()
 */
function meteologic_form_settings() {
  $form = array();

  $form['blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blocks'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['blocks']['meteologic_feed_blocks'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate a block for each feed and provider'),
    '#description' => t('By default only a single block for each feed is generated, using the selected provider. Check ths option so that regardless of which feeds and providers are enabled, a block will generated each valid combination.'),
    '#default_value' => variable_get('meteologic_feed_blocks', FALSE),
  );

  $form['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['pages']['meteologic_page_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable pages'),
    '#description' => t('Enable this to get pages as well as blocks for each meteologic feed.'),
    '#default_value' => variable_get('meteologic_page_enable', FALSE),
  );

  $form['pages']['meteologic_page_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Base path for pages'),
    '#description' => t('Define a base path for Meteologic feed pages. The default is "meteologic", so each feed will have a URL like this: meteologic/current, meteologic/radar and so on. Please not that this path will only be used as a base and will have no page of its own.'),
    '#default_value' => variable_get('meteologic_page_path', 'meteologic'),
    '#states' => array(
      'visible' => array(
        'input[name="meteologic_page_enable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['pages']['meteologic_feed_pages'] = array(
    '#type' => 'checkbox',
    '#title' => t('Generate a page for each feed and provider'),
    '#description' => t('By default only a single page for each feed is generated, using the selected provider. Check ths option so that regardless of which feeds and providers are enabled, a page will generated for each valid combination.'),
    '#default_value' => variable_get('meteologic_feed_pages', FALSE),
    '#states' => array(
      'visible' => array(
        'input[name="meteologic_page_enable"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['misc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Misc'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['misc']['meteologic_dev'] = array(
    '#type' => 'checkbox',
    '#title' => t('Development mode'),
    '#description' => t('Development mode logs more watchdog entries such as debug statments whereas production will only log errors.'),
    '#default_value' => variable_get('meteologic_dev', TRUE),
  );
  
  $form['misc']['meteologic_usebatch'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use Batch Updates'),
      '#description' => t('Require the updates to run as batch jobs. Useful if importing large amounts of data from many different feeds or locations. Not normally required.'),
      '#default_value' => variable_get('meteologic_usebatch', FALSE),
  );
  
  $form['misc']['meteologic_details_path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path to Weather Details Page'),
      '#description' => t('You can define a path to the weather details page here. defaults to "weather"'),
      '#default_value' => variable_get('meteologic_details_path', 'weather'),
  );
  
  $form['misc']['meteologic_details_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Link Text to Details'),
      '#description' => t('Set the link text for the detailed weather link.'),
      '#default_value' => variable_get('meteologic_details_text', 'Detailed Weather'),
  );
  
  $form['misc']['meteologic_dev_docu'] = array(
      '#markup' => t('<span style="font-size:smaller;">Development mode logs more watchdog entries such as debug e whereas production will only log errors.</span>'),
  );

  $form['#submit'][] = 'meteologic_form_settings_submit';

  return system_settings_form($form);
}

/**
 * Submit callback.
 * We need to rebuild the menu if the "pages" option changes.
 *
 * @see meteologic_form_settings()
 */
function meteologic_form_settings_submit(&$form, &$form_state) {
  $page_enable = variable_get('meteologic_page_enable', FALSE);

  // Value changed, must reubuild menu.
  if ($page_enable != $form_state['values']['meteologic_page_enable']) {
    variable_set('menu_rebuild_needed', TRUE);
  }
  // Value didn't change but is on; check whether the generate page for each
  // feed/provider combo changed as it will also warrant a menu rebuild.
  else if ($form_state['values']['meteologic_page_enable']) {
    $page_combo = variable_get('meteologic_feed_pages', FALSE);

    if ($page_combo != $form_state['values']['meteologic_feed_pages']) {
      variable_set('menu_rebuild_needed', TRUE);
    }
  }
}

/**
 * Form callback.
 * Displays meteologic cron settings form.
 *
 * @see meteologic_menu()
 */
function meteologic_form_settings_cron() {
  $form = array();

  $form['cron'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cron'),
    '#description' => t("Here you can manually configure which feeds from which providers are updated, if any, during cron."),
    '#collapsible' => FALSE,
    '#tree' => TRUE,
  );

  foreach (meteologic_feeds() as $feed => $feed_info) {
    if (!empty($feed_info['providers'])) {

      $form['cron'][$feed] = array(
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
//        '#collapsed' => TRUE,
        '#title' => $feed_info['name'],
        '#tree' => TRUE,
      );

      foreach ($feed_info['providers'] as $provider => $provider_info) {
        if ($provider_info['enabled']) {
          $varname = "meteologic_cron_{$feed}_{$provider}";

          $form['cron'][$feed][$provider] = array(
            '#type' => 'checkbox',
            '#title' => $provider_info['name'],
            '#default_value' => variable_get($varname, TRUE),
          );
        }
      }
    }
  }

  $form['#submit'][] = 'meteologic_form_settings_cron_submit';

  return system_settings_form($form);
}

/**
 * Submit callback.
 * I'm not sure why we need this but the form wasn't saving variables any other
 * way. @TODO come back to this later.
 */
function meteologic_form_settings_cron_submit(&$form, &$form_state) {
  foreach ($form_state['values']['cron'] as $feed => $feed_info) {
    foreach ($feed_info as $provider => $status) {
      $varname = "meteologic_cron_{$feed}_{$provider}";
      variable_set($varname, $status);
    }
  }
}

/**
 * Page callback.
 * Displays meteologic provider settings home page.
 *
 * @see meteologic_menu()
 */
function meteologic_page_providers() {
  drupal_set_title(t('Meteologic Providers'));
  $page = array();

  $links = array();
  foreach (meteologic_providers() as $name => $info) {
    if (isset($info['settings']) && !empty($info['settings'])) {
      $links[] = array(
        'title' => $info['name'],
        'href' => "admin/config/services/meteologic/providers/{$name}",
      );
    }
  }

  $page['providers'] = array(
    '#theme' => 'links',
    '#links' => $links,
    '#heading' => t('Configure settings for Meteologic providers'),
    '#attributes' => array('id' => 'meteologic-settings-providers'),
  );

  return $page;
}

/**
 * Page callback.
 * Displays meteologic feeds settings home page.
 *
 * @see meteologic_menu()
 */
function meteologic_page_feeds() {
  drupal_set_title(t('Meteologic Feeds'));
  $page = array();

  $links = array();
  foreach (meteologic_feeds() as $name => $info) {
    $links[] = array(
      'title' => $info['name'],
      'href' => "admin/config/services/meteologic/feeds/{$name}",
    );
  }

  $page['feeds'] = array(
    '#theme' => 'links',
    '#links' => $links,
    '#heading' => t('Configure settings for Meteologic feeds'),
    '#attributes' => array('id' => 'meteologic-settings-feeds'),
  );

  return $page;
}



/**
 * Form callback.
 * Displays checkboxes to include data from specific feeds for homepage and footer widgets.
 */
function meteologic_widgets_form() {
  $form = array();
  
  $form['widgetintro'] = array(
      '#type' => 'fieldset',
      '#title' => t('Meteologic Widgets'),
      '#description' => t(''),
      '#collapsible' => FALSE,
      '#tree' => TRUE,
  );
  
  $form['widgetintro']['desc'] = array(
      '#markup' => 'The meteologic module provides two configurable blocks. The \'Homepage Widget\' is intended for placement on the homepage
       while the footer/global widget is intended for placement globally. You may select what feed data is included in each widget block. Once configured, copy the provided base tpl files for each widget to your theme folder and customize.
      Preprocess functions pass data in variables named matching their corresponding theme and are available for rendering output in these customizable tpl files.',
  );

  $form['homepagewidget'] = array(
      '#type' => 'fieldset',
      '#title' => t('Homepage Widget'),
      '#description' => t('Enabled Feeds For Homepage Widget'),
      '#collapsible' => FALSE,
      '#tree' => TRUE,
  );

  $form['footerwidget'] = array(
      '#type' => 'fieldset',
      '#title' => t('Footer Widget'),
      '#description' => t('Enabled Feeds For Global Footer Widget'),
      '#collapsible' => FALSE,
      '#tree' => TRUE,
  );

  $mf = meteologic_feeds();

  if($mf){
    foreach ($mf as $name => $info) {
      $form['homepagewidget']['meteologic_homepagewidget_'.$name] = array(
          '#type' => 'checkbox',
          '#title' => $name,
          '#default_value' => variable_get('meteologic_homepagewidget_'.$name, FALSE),
      );
       
      $form['footerwidget']['meteologic_footerwidget_'.$name] = array(
          '#type' => 'checkbox',
          '#title' => $name,
          '#default_value' => variable_get('meteologic_footerwidget_'.$name, FALSE),
      );
       
    }
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Update Widgets')
  );

  return $form;
}

/**
 * Submit callback.
 * Triggers updates for the selected forecast providers.
 *
 * @see meteologic_update_form()
 */
function meteologic_widgets_form_submit($form, &$form_state) {


  foreach ($form_state['values']['homepagewidget'] as $key => $value) {
    
    variable_set($key, $value);
    
  }
  
  foreach ($form_state['values']['footerwidget'] as $key => $value) {
  
    variable_set($key, $value);
  
  }
  
}





/**
 * Form callback.
 * Display feed config form.
 *
 * @see meteologic_menu()
 */
function meteologic_form_feed_config($form, &$form_state, $feed) {
  $form = array();
  $feed_info = meteologic_feeds($feed);
  drupal_set_title(t('Meteologic Feeds - @name feed', array('@name' => $feed_info['name'])));

  $form['enabled'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enabled Providers'),
    '#description' => t('Enable or disable providers for the @name feed.', array('@name' => $feed_info['name'])),
    '#collapsible' => FALSE,
    '#tree' => TRUE,
  );

  $varname = "meteologic_fallback_{$feed}";
  $form_state['meteologic_feed'] = $feed;

  foreach ($feed_info['providers'] as $slug => $provider_info) {
    $varname = "meteologic_{$feed}_{$slug}";

    $form['enabled'][$varname] = array(
      '#type' => 'checkbox',
      '#title' => $provider_info['name'],
      '#default_value' => variable_get($varname, TRUE),
    );
  }

  if (count($feed_info['providers']) > 0) {
    $form['order'] = array(
      '#type' => 'fieldset',
      '#title' => t('Provider priority'),
      '#description' => t('If multiple providers are enabled, which one should we use?'),
      '#collapsible' => FALSE,
    );

    $varname = "meteologic_fallback_{$feed}";
    $form['order'][$varname] = array(
      '#type' => 'checkbox',
      '#title' => t('Fallback if unavailable'),
      '#description' => t('If the selected provider is unavailable, display the results for the next available one.'),
      '#default_value' => variable_get($varname, FALSE),
    );

    $form['order']['providers'] = array(
      '#tree' => TRUE,
    );

    $weights = variable_get("meteologic_weight_{$feed}", array());

    if (empty($weights)) {
      // This option hasn't been set yet, so manually populate the
      // providers that implement this feed.
      foreach ($feed_info['providers'] as $slug => $provider_info) {
        $weights[$slug] = 0;
      }
    }

    foreach ($weights as $slug => $weight) {
      $form['order']['providers'][$slug] = array(
        'name' => array(
          '#markup' => $provider_info['name'],
        ),
        'weight' => array(
          '#type' => 'weight',
          '#title' => t('Weight'),
          '#default_value' => $weight,
          '#delta' => 10,
          '#title-display' => 'invisible',
        ),
      );
    }
  }
  else {
    $form['enabled']['empty'] = array(
      '#prefix' => '<div class="empty">',
      '#suffix' => '</div>',
      '#markup' => t('No providers implement this feed!'),
    );
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Changes')
  );

  return $form;
}

/**
 * Submit callback.
 *
 * @see meteologic_form_feed_config()
 */
function meteologic_form_feed_config_submit(&$form, &$form_state) {
  $values = & $form_state['values'];
  $feed = $form_state['meteologic_feed'];

  // Fallback variable.
  $varname = "meteologic_fallback_{$feed}";
  variable_set($varname, $values[$varname]);

  // Enabled providers.
  foreach ($values['enabled'] as $provider => $status) {
    variable_set($provider, $status);
  }

  if (isset($values['providers'])) {
    // Provider order.
    $order = array();

    foreach ($values['providers'] as $slug => $info) {
      $order[$slug] = $info['weight'];
    }

    asort($order);
    variable_set("meteologic_weight_{$feed}", $order);
  }
}

/**
 * Page callback.
 * Displays meteologic summary page.
 *
 * @see meteologic_menu()
 */
function meteologic_summary_page() {
  drupal_set_title(t('Meteologic Summary'));
  $meteologic_providers = meteologic_providers();
  $page = array();

  $header = array(t('Feed'));
  $rows = array();

  foreach ($meteologic_providers as $provider) {
    $header[] = $provider['name'];
  }

  foreach (meteologic_feeds() as $feed_slug => $feed) {
    $temp = array($feed['name']);

    foreach ($meteologic_providers as $provider) {
      if (array_key_exists($feed_slug, $provider['feeds'])) {
        $temp[] = 'x';
      }
      else {
        $temp[] = '';
      }
    }

    $rows[] = $temp;
  }

  $page['table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  return $page;
}

/**
 * Form callback.
 * Displays update forecast feeds form.
 */
function meteologic_update_form() {
  $form = array();

  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Manual Update'),
    '#description' => t("Here you can manually configure which feeds from which providers to update."),
    '#collapsible' => FALSE,
    '#tree' => TRUE,
  );

  foreach (meteologic_feeds() as $feed => $feed_info) {
    if (!empty($feed_info['providers'])) {

      $form['update'][$feed] = array(
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
//        '#collapsed' => TRUE,
        '#title' => $feed_info['name'],
        '#tree' => TRUE,
      );

      foreach ($feed_info['providers'] as $provider => $provider_info) {
        if ($provider_info['enabled']) {
          $form['update'][$feed][$provider] = array(
            '#type' => 'checkbox',
            '#title' => $provider_info['name'],
            '#default_value' => FALSE,
          );
        }
      }
    }
  }
  /*
   * If devel Krumo is installed then we can display the data in cache_meteologic
   * in a nice and tidy fieldset. this is use in determining what or if the meteologic cache table 
   * contains anything at all prior and after manual update

  if(module_exists('devel')){
    $form['cache_state'] = array(
        '#type' => 'fieldset',
        '#title' => t('Meteologic Cache'),
        '#description' => t("Below is the current state of Meteologic cached data."),
        '#collapsible' => FALSE,
        '#tree' => TRUE,
    );
    
    $meteologic_cache_result = db_select('cache_meteologic', 'cm')
    ->fields('cm', array('cid', 'data'))
    ->execute();
    $cachedata = array();
    foreach ($meteologic_cache_result as $meteologic_cache) {
      $cachedata[$meteologic_cache->cid] = unserialize($meteologic_cache->data);
    }
    
    $form['cache_state']['cache_data'] = array(
         '#markup' => drupal_print_message($cachedata, TRUE),
    );

  }*/
  
  

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update Feeds')
  );

  return $form;
}

/**
 * Submit callback.
 * Triggers updates for the selected forecast providers.
 *
 * @see meteologic_update_form()
 */
function meteologic_update_form_submit($form, &$form_state) {
  $feeds = array();
  
  
  foreach ($form_state['values']['update'] as $feed => $info) {
    $update = array_values($info);
    if($update[0] === 1){
      $feed = meteologic_feeds($feed);
      foreach ($info as $provider => $enabled) {
        if (!$enabled) {
          $feed['providers'][$provider]['enabled'] = FALSE;
        }
      }
      $feeds[] = $feed;
    }
  }
  
  $usebatch = variable_get('meteologic_usebatch', FALSE);
  // Use Batch API to update each one.
  if($usebatch){
    batch_set(array(
      'title' => t('Updating Meteologic feeds...'),
      'operations' => array(
        array('meteologic_update_feeds_batch', array($feeds))
      ),
      'progress_message' => t('Updated @current of @total.'),
      'error_message' => t('An error has occurred updating feed information. Please check the site logs for more information.'),
      'finished' => 'meteologic_update_feeds_batch_finished',
    ));
  
    if (variable_get('meteologic_dev', TRUE)) {
      watchdog('meteologic', 'Starting batch forecast update', array(), WATCHDOG_INFO);
    }
  
    // Start batch and redirect to update form when we're done.
    batch_process('admin/config/services/meteologic/update');
  }else{
    meteologic_update_feeds_manual($feeds);
    drupal_goto('admin/config/services/meteologic/update');
  }
 
}