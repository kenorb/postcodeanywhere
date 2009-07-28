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
  
  $form['ct_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content Type Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  
  $form['ct_settings']['pca_forms'] = array(
   '#type' => 'checkboxes',
   '#title' => t('Form IDs'),
   '#description' => t('Select content types for which you want to enable Postcodeanywhere.'),
   '#options' => node_get_types('names'),
   '#default_value' => drupal_map_assoc(variable_get('pca_forms', array())),
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
    '#default_value' => variable_get('pca_id_city', "input[id*='city-0-value'],input[id*='town-0-value']"),
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

