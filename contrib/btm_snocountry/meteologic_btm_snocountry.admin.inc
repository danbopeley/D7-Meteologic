<?php
/**
 * @file admin.sno_country_client.inc
* Sno Country Client Admin Functions
* Handles all the settings for the Sno Country Client Module
* Version: 1.0
*/

/**
 * Form callback.
 * Display settings form for Meteologic BTM Snocountry.
 */
function meteologic_btm_snocountry_settings_form() {
  // Load the modal library and add the modal javascript.
  ctools_include('modal');
  ctools_modal_add_js();
  
  $form = array();
  
  // Grab provider info.
  $provider = meteologic_providers('noaa');
  
  $form['wrapper'] = array(
      '#type' => 'fieldset',
      '#title'       => t('Sno Country Client Settings'),
      '#description' => t('Create a new connector by clicking on: New Resort.'),
      '#collapsible' => FALSE,
  );
  

  $form['wrapper']['add_resort'] = array(
      '#prefix' => t('!MSG', array('!MSG' => '<h3 class="title">Add a New Resort</h3>')),
      '#value'  => '<p>'.l('New Resort', 'admin/config/services/meteologic/providers/btm_snowcountry/resort/nojs/add', array('attributes' => array('class' => 'ctools-use-modal'))).'</p>',
      '#weight' => -50,
  );
  
 
  $resorts = variable_get('sno_country_client_blocks',array());
  if (empty($resorts)) {
    $data = t('No Resorts Added Yet.');
  } else {
    foreach ($resorts as $key => $resort) {
      $msg['!title']      = '<p>Title: '.$resort['human_name'] .' ' .l('Edit', 'admin/settings/snocountry/client/main/resort/nojs/edit/'.$resort['resort_id'], array('attributes' => array('class' => 'ctools-use-modal'))) .'</p>';
      $msg['!theme_name'] = '<p>Theme Information: ' .str_replace('_','-',$resort['theme']) .'.tpl.php</p>';
      $msg['!days']       = '<p>Accumulation Days: ' .$resort['accumulation_days'] .'</p>';
      $connection         = 'http://' .$resort['hub_url'] .'/' .$resort['resort_id'] .'/' .$resort['accumulation_days'];
      $msg['!connection'] = '<p>' .l($connection,$connection) .'</p>';
      $msg['!active']     = ($resort['active'] == TRUE) ? '<div class="message status"><p style="text-align:right;padding-right:5px;">Active</p></div>' : '<div class="message warning"><p style="text-align:right;padding-right:5px;">Inactive</p></div>';
      $options[] = t('!active !title !theme_name !days !connection',$msg);
    }
    $data = theme('item_list',$options);
  }
  
  $form['wrapper']['show_resorts'] = array(
      '#prefix'  => t('!MSG', array('!MSG' => '<h3 class="title">Resorts Added</h3>')),
      '#value'  => '<div class="admin-show-resorts">'.$data.'</div>',
      '#weight' => 50,
      '#group'  => 'main',
  );
  
  
  return system_settings_form($form);
}






/**
 * Main settings form

function _sno_country_client_main_settings() {
  // Load the modal library and add the modal javascript.
  ctools_include('modal');
  ctools_modal_add_js();
  //Make our Form, we can style it later.
  $form['main'] = array(
      '#type'        => 'fieldset',
      '#title'       => t('Sno Country Client Settings'),
      '#description' => t('Create a new connector by clicking on: New Resort.'),
      '#collapsible' => FALSE,
      '#collapsed' 	 => FALSE,
      '#weight'			 => -50,
      '#group'       => 'main',
  );
  $form['main']['add_resort'] = array(
      '#prefix' => t('!MSG', array('!MSG' => '<h3 class="title">Add a New Resort</h3>')),
      '#value'  => '<p>'.l('New Resort', 'admin/settings/snocountry/client/main/resort/nojs/add', array('attributes' => array('class' => 'ctools-use-modal'))).'</p>',
      '#weight' => -50,
      '#group'  => 'main',
  );
  $resorts = variable_get('sno_country_client_blocks',array());
  if (empty($resorts)) {
    $data = t('No Resorts Added Yet.');
  } else {
    foreach ($resorts as $key => $resort) {
      $msg['!title']      = '<p>Title: '.$resort['human_name'] .' ' .l('Edit', 'admin/settings/snocountry/client/main/resort/nojs/edit/'.$resort['resort_id'], array('attributes' => array('class' => 'ctools-use-modal'))) .'</p>';
      $msg['!theme_name'] = '<p>Theme Information: ' .str_replace('_','-',$resort['theme']) .'.tpl.php</p>';
      $msg['!days']       = '<p>Accumulation Days: ' .$resort['accumulation_days'] .'</p>';
      $connection         = 'http://' .$resort['hub_url'] .'/' .$resort['resort_id'] .'/' .$resort['accumulation_days'];
      $msg['!connection'] = '<p>' .l($connection,$connection) .'</p>';
      $msg['!active']     = ($resort['active'] == TRUE) ? '<div class="message status"><p style="text-align:right;padding-right:5px;">Active</p></div>' : '<div class="message warning"><p style="text-align:right;padding-right:5px;">Inactive</p></div>';
      $options[] = t('!active !title !theme_name !days !connection',$msg);
    }
    $data = theme('item_list',$options);
  }
  $form['main']['show_resorts'] = array(
      '#prefix'  => t('!MSG', array('!MSG' => '<h3 class="title">Resorts Added</h3>')),
      '#value'  => '<div class="admin-show-resorts">'.$data.'</div>',
      '#weight' => 50,
      '#group'  => 'main',
  );
  //Enable vertical tabs if installed.
  $form['#pre_render'][] = 'vertical_tabs_form_pre_render';
  return $form;
}
*/
/**
 * _sno_country_client_main_settings_callback()
 * The callback for our modal dialogue form
 
function _sno_country_client_main_settings_callback($js = FALSE, $op = NULL, $resort_id = NULL) {
  if ($js) {
    ctools_include('ajax');
    ctools_include('modal');
    switch ($op) {
      case 'add':
        $title = t('Add A Resort Connection');
        break;
      case 'edit':
        $title = t('Edit Resort Connection');
        break;
    }
    $form_state = array(
        'ajax'  => TRUE,
        'title' => $title,
        'args'  => array(
            'op'        => $op,
            'resort_id' => $resort_id
        ),
    );
    $output = ctools_modal_form_wrapper('_sno_country_add_resort', $form_state);
    if (empty($output)) {
      $output[] = ctools_modal_command_loading();
      $output[] = ctools_ajax_command_redirect('admin/settings/snocountry/client/main');
    }
    ctools_ajax_render($output);
  } else {
    drupal_set_title($title);
    return $output;
  }
}
*/
/**
 * _sno_country_add_resort()
 
function _sno_country_add_resort($js = FALSE, $op = NULL, $resort_id = NULL) {
  if (!empty($resort_id)) {
    $resorts = variable_get('sno_country_client_blocks',array());
    $resort = $resorts[$resort_id];
  } else {
    $resort['hub_url'] = SNO_COUNTRY_CLIENT_HOSTS_DEFAULT;
    $resort['active']  = TRUE;
  }
  $form['add_resort'] = array(
      '#action' => 'admin/settings/snocountry/client/main',
      '#submit' => '_sno_country_add_resort_submit',
  );
  $form['add_resort']['machine_name'] = array(
      '#title'         => t('Machine Name'),
      '#description'   => t('The machine name for this resort. This is restricted to 12 characters, and will be used for the block name and template identifier name and may only contain hyphens.'),
      '#type'          => 'textfield',
      '#required'      => TRUE,
      '#default_value' => $resort['machine_name'],
      '#max_length'    => 12,
      '#weight'        => -50,
  );
  $form['add_resort']['human_name'] = array(
      '#title'         => t('Machine Name'),
      '#description'   => t('The human name for this resort. This is to identify the resort in the admin section and in blocks.'),
      '#type'          => 'textfield',
      '#required'      => TRUE,
      '#default_value' => $resort['human_name'],
      '#max_length'    => 12,
      '#weight'        => -49,
  );
  $form['add_resort']['hub_url'] = array(
      '#title'         => t('Sno Country Hub URL'),
      '#description'   => t('The URL where you want to query the server. Defaults to: ski.bluetent.com'),
      '#type'          => 'textfield',
      '#required'      => TRUE,
      '#default_value' => $resort['hub_url'],
      '#max_length'    => 12,
      '#weight'        => -48,
  );
  $form['add_resort']['resort_id'] = array(
      '#title'         => t('Resort ID or Sno Country Hub Key'),
      '#description'   => t('The six digit Resort ID or API key for the Snow Country Hub connection.'),
      '#type'          => 'textfield',
      '#required'      => TRUE,
      '#default_value' => $resort['resort_id'],
      '#max_length'    => 12,
      '#weight'        => -47,
  );
  $days = array(
      '' => t('Select'),
      4  => t('Four Days'),
      5  => t('Five Days'),
      9  => t('Nine Days'),
  );
  $form['add_resort']['accumulation_days'] = array(
      '#title'         => t('Accumulation Days'),
      '#description'   => t('The accumulative historical data for snow depth. Either, 4 Days, 5 Days or 9 Days.'),
      '#type'          => 'select',
      '#required'      => TRUE,
      '#options'       => $days,
      '#default_value' => $resort['accumulation_days'],
      '#weight'        => -46,
  );
  $form['add_resort']['active'] = array(
      '#title'         => t('Active'),
      '#description'   => t('Is this block active? Check this box to make this resort active.'),
      '#type'          => 'checkbox',
      '#required'      => TRUE,
      '#options'       => array(TRUE,FALSE),
      '#default_value' => $resort['active'],
      '#weight'        => -45,
  );
  $form['add_resort']['submit'] = array(
      '#type'  => 'submit',
      '#value' => 'Save Resort',
  );
  if ($op == 'edit') {
    //Add A Delete Button, so we can delete resorts.
    $form['add_resort']['delete'] = array(
        '#type'  => 'submit',
        '#value' => 'Delete Resort',
    );
  }
  return $form;
}

/**
 * _sno_country_add_resort_submit()

function _sno_country_add_resort_submit($form_id, &$form_state) {
  //Get A List of resorts.
  $resorts = variable_get('sno_country_client_blocks',array());
  $status  = 'status';
  //Uf we are editing or adding, same form execution.
  if ($form_state['values']['op'] != 'Delete Resort') {
    //Set the theme name from the machine name
    $machine_name = strtolower(preg_replace('[^A-Za-z0-9-_]','-',$form_state['values']['machine_name']));
    $theme_name   = 'sno_country_client_block__' .$machine_name;
    $resorts[$form_state['values']['resort_id']] = array(
        'machine_name'      => $machine_name,
        'human_name'        => t($form_state['values']['human_name']),
        'accumulation_days' => $form_state['values']['accumulation_days'],
        'hub_url'           => $form_state['values']['hub_url'],
        'resort_id'         => $form_state['values']['resort_id'],
        'theme'             => $theme_name,
        'active'            => $form_state['values']['active'],
    );
    $msg = t('Resort Saved.');
  } else {
    //If we are deleting, unset the resort from the array.
    unset($resorts[$form_state['values']['resort_id']]);
    $msg = t('Resort Deleted.');
    $status  = 'warning';
  }
  //Set a Message.
  drupal_set_message($msg,$status);
  //Set the resort variable.
  variable_set('sno_country_client_blocks',$resorts);
}

*/