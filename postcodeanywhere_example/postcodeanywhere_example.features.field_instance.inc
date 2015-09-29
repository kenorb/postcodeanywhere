<?php
/**
 * @file
 * postcodeanywhere_example.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function postcodeanywhere_example_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'entityform-postcode_anywhere_example-field_pca_field'
  $field_instances['entityform-postcode_anywhere_example-field_pca_field'] = array(
    'bundle' => 'postcode_anywhere_example',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_pca_field',
    'label' => 'Post code (text)',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'postcodeanywhere_field',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'postcodeanywhere_text',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'entityform-postcode_anywhere_example-field_pca_field_autocomplete'
  $field_instances['entityform-postcode_anywhere_example-field_pca_field_autocomplete'] = array(
    'bundle' => 'postcode_anywhere_example',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'entityform',
    'field_name' => 'field_pca_field_autocomplete',
    'label' => 'Post code (autocomplete)',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'postcodeanywhere_field',
      'settings' => array(
        'autocomplete_path' => 'pca/autocomplete',
        'size' => 60,
      ),
      'type' => 'postcodeanywhere_autocomplete',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Post code (autocomplete)');
  t('Post code (text)');

  return $field_instances;
}
