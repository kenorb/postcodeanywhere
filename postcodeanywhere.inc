<?php

/**
 * @file
 *   Include file to handle the PCA callbacks.
 */

/**
 * AJAX callback to lists address records for the given postcode.
 */
function postcodeanywhere_autocomplete($string = "") {
  $data = array();

  $string = str_replace(array(' ', '%20'), '', strtolower($string)); // Make a string lowercase and remove all spaces.
  $addressfield = module_exists('postcodeanywhere_field') && module_exists('addressfield');
  try {
    $data = postcodeanywhere_findbypostcode($string, TRUE);
    if ($data && $addressfield) {
      $data = postcodeanywhere_autocomplete_addressfield($data, $string, TRUE);
    } else if (empty($data)) {
      $data = array('count-details' => t(":result found, keep typing to refine", array('result' => format_plural(count($data), t('1 result'), '@count ' . t('results.')))));
    }
  }
  catch (Exception $e) {
    // Check logs for further details.
    $data = array('no-match' => t("I can't see my address."));
  }
  drupal_json_output($data);

  /*
  if (strlen($string) >= 5) { // If postcode is 5 chars in length or more, it's full post code ...
    postcodeanywhere_findbypostcode($string);
  }
  else if (strlen($string) >= 2) { // ... otherwise if it's 3-4 in length, it's partial.
    postcodeanywhere_findbypartialpostcode($string);
  } else {
    drupal_json_output($matches);
  }
  */
}

/**
 * Help function to parse postcode data for addressfield.
 */
function postcodeanywhere_autocomplete_addressfield($data = array(), $postcode = "", $returnArray = FALSE) {

  $outArray = array();
  foreach ($data as $key => $value) {
    // If we don't have a StreetAddress, this isn't a location
    if (isset($value->StreetAddress)) {
      $buildArray[$value->Id] = $value->StreetAddress . ", " . $value->Place . ", " . strtoupper($postcode);
    } elseif (isset($value->Place)) {
      // @todo? Partial postcodede
      // $buildArray[$value->Id[0]] = $value->Place[0];
    } else {
      // Nothing
    }
  }

  $count_out = count($buildArray);
  if($count_out > 0) {
    $outArray = array_merge(
        array('count-details' => t(":result found, keep typing to refine", array('result' => format_plural($count_out, t('1 result'), '@count ' . t('results.')))),
        $buildArray,
        array('no-match' => t("I can't see my address.")))
      );
  }

  return $returnArray ? $outArray : drupal_json_output($outArray);
}

/**
 * Form element validate handler for PCA autocomplete element.
 */
function postcodeanywhere_autocomplete_validate($element, &$form_state) {
  $values = $form_state['values'];

  // @todo? strlen($string) <= 3
  // form_error($form['node'], t('Sorry, the post code is too short.'));
}

/**
 * AJAX callback to lists address records for the given postcode.
 */
function postcodeanywhere_findbypostcode($postcode = PCA_PC_TEST, $returnArray = FALSE) {
  require_once(drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_FindByPostcode.class.inc");
  $key = variable_get('postcodeanywhere_licence', PCA_DEMO_KEY);
  $cid = str_replace(' ', '', "pca_pc_" . $postcode);

  if (!($data = _pca_get_cache($cid))) {
    try {
      $pca = new PostcodeAnywhere_Interactive_FindByPostcode($key, $postcode, "");
      $pca->MakeRequest();
      if ($data = $pca->HasData()) {
        _pca_set_cache($cid, $data);
      } else {
        $data = array();
      }
    }
    catch (Exception $e) {
      watchdog_exception('postcodeanywhere', $e);
      throw new Exception($e->getMessage());
    }
  }
  return $returnArray ? $data : drupal_json_output($data);
}

/**
 * AJAX callback to lists address records for the given postcode.
 */
function postcodeanywhere_findbypartialpostcode($PartialPostcode = "WR2", $returnArray = FALSE) {
  require_once(drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_FindByPartialPostcode.class.inc");
  $key = variable_get('postcodeanywhere_licence', PCA_DEMO_KEY);
  $cid = str_replace(' ', '', "pca_pc_" . $PartialPostcode);

  if (!($data = _pca_get_cache($cid))) {
    try {
      $pca = new PostcodeAnywhere_Interactive_FindByPartialPostcode($key, $PartialPostcode, "");
      $pca->MakeRequest();
      if ($data = $pca->HasData()) {
        _pca_set_cache($cid, $data);
      } else {
        $data = array();
      }
    }
    catch (Exception $e) {
      watchdog_exception('postcodeanywhere', $e);
      throw new Exception($e->getMessage());
    }
  }
  return $returnArray ? $data : drupal_json_output($data);
}

/**
 * AJAX callback to returns the full address details based on the Id.
 */
function postcodeanywhere_retrievebyid($id) {
  require_once(drupal_get_path('module', 'postcodeanywhere') . "/classes/PostcodeAnywhere_Interactive_RetrieveById.class.inc");
  $key = variable_get('postcodeanywhere_licence', PCA_DEMO_KEY);
  $cid = str_replace(' ', '', "pca_id_" . $id);

  if (!($data = _pca_get_cache($cid))) {
    try {
      $pca = new PostcodeAnywhere_Interactive_RetrieveById($key, $id, "English", "");
      $pca->MakeRequest();
      if ($data = $pca->HasData()) {
        _pca_set_cache($cid, $data);
      } else {
        $data = array();
      }
    }
    catch (Exception $e) {
      watchdog_exception('postcodeanywhere', $e);
      throw new Exception($e->getMessage());
    }
  }
  drupal_json_output($data);
}

/**
 * Helper function to get results from cache.
 */
function _pca_get_cache($cid) {
  $format = variable_get('postcodeanywhere_format', PCA_FORMAT);
  if ($cache = cache_get($cid, PCA_CACHE)) {
    // Serialization of SimpleXMLElement is not alloweḑ, so doing some workaround.
    $data = $format == 'xmla.ws' ? json_decode($cache->data) : $cache->data;
  }
  if (!empty($data)) {
    drupal_add_http_header('X-Cached-By', 'Drupal PCA');
    return $data;
  } else {
    return FALSE;
  }
}

/**
 * Helper function to cache the results.
 */
function _pca_set_cache($cid, $data) {
  $format = variable_get('postcodeanywhere_format', PCA_FORMAT);
  // Serialization of SimpleXMLElement is not alloweḑ, so doing some workaround.
  return cache_set($cid,  $format == 'xmla.ws' ? json_encode($data) : $data , PCA_CACHE);
}
