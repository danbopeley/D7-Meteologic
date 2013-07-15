<?php

/**
 * @file
 * Default module implementation to display the meteologic_homepagewidget block.
 *
 * Available variables:
 * - $block->subject: Block title
 * a data container for each meteologic feed currently enabled to show in the homepage widget settings 
 * @url admin/config/services/meteologic/widgets
 * @see meteologic.module :: meteologic_prerender_homepagewidget()
 * @see theme/meteologic.theme.inc :: meteologic_preprocess_meteologic_homepagewidget()
 * 
 * @ingroup themeable
 * 
 * CUSTOMISIBLE THEME IMPLEMENTATION
 * copy this file to your theme folder
 * add meteologic_preprocess_meteologic_homepagewidget(&$vars){}
 * to your themes template.php where you can set/modified data from supplied feeds
 * 
 */

if($current) {
  kpr($current);
}
if($forecast) {
  kpr($forecast);
}

?>
<div class="meteologic-data-wrapper">Copy This File to you theme directory and customise</div>