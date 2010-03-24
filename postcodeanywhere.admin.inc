<?php

/**
 * @file
 *   Form settings include file
 *
 * @version
 *   $Id$
 *
 * @developers
 *   Rafal Wieczorek <kenorb@gmail.com>
 */

/**
 * Implementation of menu callback
 */
function postcodeanywhere_settings_form(&$form_state) {

  $form['license'] = array(
    '#type' => 'fieldset',
    '#title' => t('License settings'),
    '#description' => t('Account settings.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $yesno_option = array(1 => 'YES', 0 => 'NO');

  $form['license']['pca_account_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Account Code'),
    '#default_value' => variable_get('pca_account_code', ''),
  );
  
  $form['license']['pca_licence'] = array(
    '#type' => 'textfield',
    '#title' => t('Licence Key'),
    '#default_value' => variable_get('pca_licence', ''),
  );
  
  $form['license']['pca_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Postcodeanywhere URL'),
    '#default_value' => variable_get('pca_url', 'http://services.postcodeanywhere.co.uk/inline.aspx'),
  );
  
  $form['page_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page specific visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['page_vis_settings']['pca_forms'] = array(
   '#type' => 'checkboxes',
   '#title' => t('Content Types'),
   '#description' => t('Select content types for which you want to activate Postcodeanywhere.'),
   '#options' => node_get_types('names'),
   '#default_value' => drupal_map_assoc(variable_get('pca_forms', array())),
  );

  $access = user_access('use PHP for postcodeanywhere visibility');
  if ($edit['visibility'] == 2 && !$access) {
    $form['page_vis_settings'] = array();
    $form['page_vis_settings']['pca_page_visibility_mode'] = array('#type' => 'value', '#value' => 2);
    $form['page_vis_settings']['pca_page_visibility_rules'] = array('#type' => 'value', '#value' => $edit['pages']);
  }
  else {
    $options = array(t('Show on every page except the listed pages.'), t('Show on only the listed pages.'));
    $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));

    if ($access) {
      $options[] = t('Show if the following PHP code returns <code>TRUE</code> (PHP-mode, experts only).');
      $description .= ' '. t('If the PHP-mode is chosen, enter PHP code between %php. Note that executing incorrect PHP-code can break your Drupal site.', array('%php' => '<?php ?>'));
    }
    $form['page_vis_settings']['pca_page_visibility_mode'] = array(
      '#type' => 'radios',
      '#title' => t('Activate on specific pages'),
      '#options' => $options,
      '#default_value' => variable_get('pca_page_visibility_mode', ''),
    );
    $form['page_vis_settings']['pca_page_visibility_rules'] = array(
      '#type' => 'textarea',
      '#title' => t('Pages'),
      '#default_value' => variable_get('pca_page_visibility_rules', ''),
      '#description' => $description,
    );
  }

/*
  $form['ct_settings']['pca_forms'] = array(
   '#type' => 'checkboxes',
   '#title' => t('Content Types'),
   '#description' => t('Select content types for which you want to activate Postcodeanywhere.'),
   '#options' => node_get_types('names'),
   '#default_value' => drupal_map_assoc(variable_get('pca_forms', array())),
  );
*/


  $form['form_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form Selectors'),
    '#description' => t('Choose proper jQuery selectors'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['form_settings']['pca_id_postcode_wrapper'] = array(
    '#type' => 'textfield',
    '#title' => t('Postcode Wrapper (i.e. parent DIV tag)'),
    '#default_value' => variable_get('pca_id_postcode_wrapper', "div[id*='wrapper'][id*='postcode'],label[for*='postcode']"),
    '#description' => t('XPath to existing wrapper where button should appear.'),
  );
  
  $form['form_settings']['pca_id_input_postcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postcode Input'),
    '#default_value' => variable_get('pca_id_input_postcode', "input[id*='postcode-0-value']"),
    '#description' => t('XPath to existing input field of Postcode.'),
  );
  
  $form['form_settings']['pca_id_house_number'] = array(
    '#type' => 'textfield',
    '#title' => t('House Number'),
    '#default_value' => variable_get('pca_id_house_number', "input[id*='house-']"),
    '#description' => t('XPath to existing input field of House Number.'),
  );
  
  $form['form_settings']['pca_id_property_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Property Name'),
    '#default_value' => variable_get('pca_id_property_name', "input[id*='property-']"),
    '#description' => t('XPath to existing input field of Property Name.'),
  );
  
  $form['form_settings']['pca_id_street'] = array(
    '#type' => 'textfield',
    '#title' => t('Street Name'),
    '#default_value' => variable_get('pca_id_street', "input[id*='address-0-value']"),
    '#description' => t('XPath to existing input field of Street Name.'),
  );
  
  $form['form_settings']['pca_id_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City Name'),
    '#default_value' => variable_get('pca_id_city', "input[id*='city-0-value'],input[id*='town-0-value']"),
    '#description' => t('XPath to existing input field of City Name.'),
  );
  
  $form['form_settings']['pca_id_county'] = array(
    '#type' => 'textfield',
    '#title' => t('County Name'),
    '#default_value' => variable_get('pca_id_county', "input[id*='county-0-value']"),
    '#description' => t('XPath to existing input field of County Name.'),
  );
  
  $form['form_settings']['pca_id_country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country Name'),
    '#default_value' => variable_get('pca_id_country', "input[id*='country-0-value']"),
    '#description' => t('XPath to existing input field of Country Name.'),
  );
  
  $form['other_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form Settings'),
    '#description' => t('Form Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['other_settings']['pca_id_uk_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Country ID'),
    '#description' => t('Type here @no for UK', array('@no' => 226)),
    '#default_value' => variable_get('pca_id_uk_value', 226),
  );
  
  $form['other_settings']['pca_showalert'] = array(
    '#type' => 'select',
    '#title' => t('Show PCA Errors'),
    '#default_value' => variable_get('pca_showalert', 1),
    '#options' => $yesno_option,
  );
  
  return system_settings_form($form);
}

/**
 * Form API callback to validate the settings form.
 */
function postcodeanywhere_settings_form_validate($form, &$form_state) {
  $values = &$form_state['values'];
}

