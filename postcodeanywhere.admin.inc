<?php

/**
 * @file
 * Handles the admin forms.
 */

function postcodeanywhere_settings_form($form, &$form_state) {

  $form['license'] = array(
    '#type' => 'fieldset',
    '#title' => t('License settings'),
    '#description' => t('Account settings.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['license']['postcodeanywhere_licence'] = array(
    '#type' => 'textfield',
    '#title' => t('Web service Key'),
    '#default_value' => variable_get('postcodeanywhere_licence', ''),
  );

  $form['license']['postcodeanywhere_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Postcodeanywhere URL'),
    '#default_value' => variable_get('postcodeanywhere_url', 'http://services.postcodeanywhere.co.uk/inline.aspx'),
  );

  $form['page_vis_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page specific visibility settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $access = user_access('use PHP for postcodeanywhere visibility');
  if (!$access) { // FIXME: Not tested under Drupal 7 (See block.admin.inc for some example)
    $form['page_vis_settings'] = array();
    $form['page_vis_settings']['postcodeanywhere_page_visibility_mode'] = array('#type' => 'value', '#value' => 2);
    $form['page_vis_settings']['postcodeanywhere_page_visibility_rules'] = array('#type' => 'value', '#value' => $edit['pages']);
  }
  else {
    $options = array(t('Show on every page except the listed pages.'), t('Show on only the listed pages.'));
    $description = t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));

    if ($access) {
      $options[] = t('Show if the following PHP code returns <code>TRUE</code> (PHP-mode, experts only).');
      $description .= ' ' . t('If the PHP-mode is chosen, enter PHP code between %php. Note that executing incorrect PHP-code can break your Drupal site.', array('%php' => '<?php ?>'));
    }
    $form['page_vis_settings']['postcodeanywhere_page_visibility_mode'] = array(
      '#type' => 'radios',
      '#title' => t('Activate on specific pages'),
      '#options' => $options,
      '#default_value' => variable_get('postcodeanywhere_page_visibility_mode', ''),
    );
    $form['page_vis_settings']['postcodeanywhere_page_visibility_rules'] = array(
      '#type' => 'textarea',
      '#title' => t('Pages'),
      '#default_value' => variable_get('postcodeanywhere_page_visibility_rules', ''),
      '#description' => $description,
    );
  }

  $form['form_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form Selectors'),
    '#description' => t('Choose proper jQuery selectors'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['form_settings']['postcodeanywhere_id_wrapper'] = array(
    '#type' => 'textarea',
    '#title' => t('Postcode Wrapper (i.e. parent DIV tag)'),
    '#default_value' => variable_get('postcodeanywhere_id_wrapper', "div[id*='postcode-wrapper']"),
    '#description' => t('jQuery selector for the element where an addresslist textfield will be appended to the end of.'),
    '#required' => TRUE,
  );

  $form['form_settings']['postcodeanywhere_id_postcode'] = array(
    '#type' => 'textarea',
    '#title' => t('Postcode Input'),
    '#default_value' => variable_get('postcodeanywhere_id_postcode', "input[id*='edit-address-postcode']"),
    '#description' => t('jQuery selector for the existing postcode input field. The lookup button will be inserted immediately after this.'),
    '#required' => TRUE,
  );

  $form['form_settings']['postcodeanywhere_id_country'] = array(
    '#type' => 'textarea',
    '#title' => t('Country'),
    '#default_value' => variable_get('postcodeanywhere_id_country', "select[id*='edit-address-country']"),
    '#description' => t('jQuery selector for existing input field for Country Name.'),
  );

  $form['form_settings']['postcodeanywhere_id_company'] = array(
    '#type' => 'textarea',
    '#title' => t('Company'),
    '#default_value' => variable_get('postcodeanywhere_id_company', "input[id*='edit-address-company']"),
    '#description' => t('jQuery selector for existing input field for Address line 1.'),
  );

  $form['form_settings']['postcodeanywhere_id_company_wrapper'] = array(
    '#type' => 'textarea',
    '#title' => t('Company Wrapper'),
    '#default_value' => variable_get('postcodeanywhere_id_company_wrapper', "div.form-item-address-company"),
    '#description' => t('jQuery selector for existing input field for Company Wrapper.'),
  );

  $form['form_settings']['postcodeanywhere_id_line1'] = array(
    '#type' => 'textarea',
    '#title' => t('Address Line 1'),
    '#default_value' => variable_get('postcodeanywhere_id_line1', "input[id*='edit-address-line1']"),
    '#description' => t('jQuery selector for existing input field for Address line 1.'),
  );

  $form['form_settings']['postcodeanywhere_id_line1_wrapper'] = array(
    '#type' => 'textarea',
    '#title' => t('Address Line 1 Wrapper'),
    '#default_value' => variable_get('postcodeanywhere_id_line1_wrapper', "div.form-item-address-line1"),
    '#description' => t('jQuery selector for existing input field for Address line 1 Wrapper.'),
  );

  $form['form_settings']['postcodeanywhere_id_line2'] = array(
    '#type' => 'textarea',
    '#title' => t('Address Line 2'),
    '#default_value' => variable_get('postcodeanywhere_id_line2', "input[id*='edit-address-line2']"),
    '#description' => t('jQuery selector for existing input field for Address line 2.'),
  );

  $form['form_settings']['postcodeanywhere_id_line2_wrapper'] = array(
    '#type' => 'textarea',
    '#title' => t('Address Line 2 Wrapper'),
    '#default_value' => variable_get('postcodeanywhere_id_line2_wrapper', "div.form-item-address-line2"),
    '#description' => t('jQuery selector for existing input field for Address line 2 Wrapper.'),
  );

  $form['form_settings']['postcodeanywhere_id_line3'] = array(
    '#type' => 'textarea',
    '#title' => t('Address Line 3'),
    '#default_value' => variable_get('postcodeanywhere_id_line3', "input[id*='edit-address-line3']"),
    '#description' => t('jQuery selector for existing input field for Address line 3.'),
  );

  $form['form_settings']['postcodeanywhere_id_line3_wrapper'] = array(
    '#type' => 'textarea',
    '#title' => t('Address Line 3 Wrapper'),
    '#default_value' => variable_get('postcodeanywhere_id_line3_wrapper', "div.form-item-address-line3"),
    '#description' => t('jQuery selector for existing input field for Address line 3 Wrapper.'),
  );

  $form['form_settings']['postcodeanywhere_id_town'] = array(
    '#type' => 'textarea',
    '#title' => t('Town'),
    '#default_value' => variable_get('postcodeanywhere_id_town', "input[id*='edit-address-city']"),
    '#description' => t('jQuery selector for existing input field for Town Name.'),
  );

  $form['form_settings']['postcodeanywhere_id_town_wrapper'] = array(
    '#type' => 'textarea',
    '#title' => t('Town Wrapper'),
    '#default_value' => variable_get('postcodeanywhere_id_town_wrapper', "div.form-item-address-city"),
    '#description' => t('jQuery selector for existing input field for Town Wrapper.'),
  );

  $form['form_settings']['postcodeanywhere_id_county'] = array(
    '#type' => 'textarea',
    '#title' => t('County'),
    '#default_value' => variable_get('postcodeanywhere_id_county', "input[id*='edit-address-county']"),
    '#description' => t('jQuery selector for existing input field for County Name.'),
  );

  $form['form_settings']['postcodeanywhere_id_county_wrapper'] = array(
    '#type' => 'textarea',
    '#title' => t('County Wrapper'),
    '#default_value' => variable_get('postcodeanywhere_id_county_wrapper', "div.form-item-address-county"),
    '#description' => t('jQuery selector for existing input field for county Wrapper.'),
  );

  $form['other_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form Settings'),
    '#description' => t('Form Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['other_settings']['postcodeanywhere_id_country_uk_value'] = array(
    '#type' => 'textfield',
    '#title' => t('GB Country Key'),
    '#description' => t('Type here the value for uk in country select'),
    '#default_value' => variable_get('postcodeanywhere_id_country_uk_value', 'GB'),
  );
  $form['other_settings']['postcodeanywhere_submit_label_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Submit button label'),
    '#description' => t('Enter the label for the form submit button.'),
    '#default_value' => variable_get('postcodeanywhere_submit_label_value', 'Find address'),
  );

  return system_settings_form($form);
}
