<?php
/**
 * @file
 * postcodeanywhere_example.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function postcodeanywhere_example_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_pca_field'.
  $field_bases['field_pca_field'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_pca_field',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'postcodeanywhere_field',
    'settings' => array(
      'max_length' => 10,
    ),
    'translatable' => 0,
    'type' => 'postcodeanywhere',
  );

  // Exported field_base: 'field_pca_field_autocomplete'.
  $field_bases['field_pca_field_autocomplete'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_pca_field_autocomplete',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'postcodeanywhere_field',
    'settings' => array(
      'max_length' => 50,
    ),
    'translatable' => 0,
    'type' => 'postcodeanywhere',
  );

  return $field_bases;
}
