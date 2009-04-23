<?php
// $Id

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
  
  $form['ct_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content Type Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $types = content_types();
  $options = array();
  
  foreach ($types as $key => $value) {
    $key .= "_node_form";
    $options[$key] = $value['name'];
  }
  
  $enabled_types = variable_get('pca_forms', array());
  if(!is_array($enabled_types)) {
    $enabled_types = unserialize($enabled_types);
  }
  
  $form['ct_settings']['pca_forms'] = array(
   '#type' => 'checkboxes',
   '#title' => t('Form IDs'),
   '#description' => t('Select content types for which you want to enable Postcodeanywhere.'),
   '#options' => $options,
   '#default_value' => $enabled_types,
  );

  $form['form_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form Selectors'),
    '#description' => t('Choose proper jQuery selectors'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['form_settings']['pca_id_postcode_wrapper'] = array(
    '#type' => 'textfield',
    '#title' => t('Postcode Div Wrapper'),
    '#default_value' => variable_get('pca_id_postcode_wrapper', "div[id*='wrapper'][id*='postcode']"),
  );
  
  $form['form_settings']['pca_id_input_postcode'] = array(
    '#type' => 'textfield',
    '#title' => t('Postcode Input'),
    '#default_value' => variable_get('pca_id_input_postcode', "input[id*='postcode-0-value']"),
  );
  
  $form['form_settings']['pca_id_house_number'] = array(
    '#type' => 'textfield',
    '#title' => t('House Number'),
    '#default_value' => variable_get('pca_id_house_number', "input[id*='house-']"),
  );
  
  $form['form_settings']['pca_id_property_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Property Name'),
    '#default_value' => variable_get('pca_id_property_name', "input[id*='property-']"),
  );
  
  $form['form_settings']['pca_id_street'] = array(
    '#type' => 'textfield',
    '#title' => t('Street Name'),
    '#default_value' => variable_get('pca_id_street', "input[id*='address-0-value']"),
  );
  
  $form['form_settings']['pca_id_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City Name'),
    '#default_value' => variable_get('pca_id_city', "input[id*='city-0-value']"),
  );
  
  $form['form_settings']['pca_id_county'] = array(
    '#type' => 'textfield',
    '#title' => t('County Name'),
    '#default_value' => variable_get('pca_id_county', "input[id*='county-0-value']"),
  );
  
  $form['form_settings']['pca_id_country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country Name'),
    '#default_value' => variable_get('pca_id_country', "input[id*='country-0-value']"),
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
  
  $form['other_settings']['showerror'] = array(
    '#type' => 'select',
    '#title' => t('Show PCA Errors'),
    '#default_value' => variable_get('pca_showalert', 1),
    '#options' => $yesno_option,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Configuration'),
  );

  return $form;
}

/**
* General submit handler for Booking Timeslots configuration form.
*
* Assign values to db variables.
*
*/
function postcodeanywhere_settings_form_submit($form, &$form_state) {
  variable_set('pca_account_code', $form_state['values']['pca_account_code']);
  variable_set('pca_licence', $form_state['values']['pca_licence']);
  variable_set('pca_url', $form_state['values']['pca_url']);
  variable_set('pca_id_postcode_wrapper', $form_state['values']['pca_id_postcode_wrapper']);
  variable_set('pca_id_input_postcode', $form_state['values']['pca_id_input_postcode']);
  variable_set('pca_id_house_number', $form_state['values']['pca_id_house_number']);
  variable_set('pca_id_property_name', $form_state['values']['pca_id_property_name']);
  variable_set('pca_id_street', $form_state['values']['pca_id_street']);
  variable_set('pca_id_city', $form_state['values']['pca_id_city']);
  variable_set('pca_id_county', $form_state['values']['pca_id_county']);
  variable_set('pca_id_country', $form_state['values']['pca_id_country']);
  variable_set('pca_id_uk_value', $form_state['values']['pca_id_uk_value']);
  variable_set('pca_showalert', $form_state['values']['pca_showalert']);
  
  $forms = array();
  $data = $form_state['values']['pca_forms'];
  foreach($data as $key => $value) {
    if( strlen( $value ) > 1 ) {
      $forms[$key] = $value;
    }
  }
  variable_set('pca_forms', serialize($forms));
  
  drupal_set_message('The configuration has been saved.');
  $form_state['redirect'] = 'admin/settings/postcodeanywhere';
}
