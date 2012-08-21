<?php
/**
 * @file
 * Meteologic admin pages.
 */

/**
 * Form callback.
 * Displays main meteologic settings form.
 */
function meteologic_settings_form() {
  $form = array();

  

  return system_settings_form($form);
}