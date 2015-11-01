<?php

/**
 * @file
 * Defines postcodeanywhere_field module themes.
 */

/**
 * Returns HTML for a postcodeanywhere form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #size, #maxlength,
 *     #required, #attributes, #autocomplete_path.
 *
 * @ingroup themeable
 */
function theme_postcodeanywhere($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes($element, array('id', 'name', 'value', 'size', 'maxlength'));
  _form_set_class($element, array('form-text'));

  $extra = '';
  if ($element['#autocomplete_path'] && drupal_valid_path($element['#autocomplete_path'])) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  // Append lookup button field
  /*
  $lookup_button = array();
  $lookup_button['type'] = 'button';
  $lookup_button['id'] = $element['#attributes']['id'] . '-lookup-button';
  $lookup_button['value'] = variable_get('postcodeanywhere_submit_label_value', 'Find address');
  $extra .= '<input' . drupal_attributes($lookup_button) . ' />';
  */

  // Append address list field
  /*
  $address_list = array();
  $address_list['type'] = 'select';
  $address_list['id'] = $element['#attributes']['id'] . '-address-list';
  $address_list['size'] = '10';
  $address_list['style'][] = 'display:none';
  $extra .= '<br><select' . drupal_attributes($address_list) . ' />';
  */

  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  return $output . $extra;
}
