<?php

/**
 * @file
 * Handles the postcodeanywhere classes.
 */

/**
 * This class handles the initial request for the list of addresses at a single postcode. 
 */
class PostcodeAnywhere_Interactive_FindByPostcode_v1_00 {

  // Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

  private $Key;        // The key to use to authenticate to the service.
  private $Postcode;   // The postcode to search with find.
  private $UserName;   // The username associated with the Royal Mail license (not required for click licenses).
  private $Data;       // Holds the results of the query.

  function PostcodeAnywhere_Interactive_FindByPostcode_v1_00($Key, $Postcode, $UserName) {
    $this->Key = $Key;
    $this->Postcode = $Postcode;
    $this->UserName = $UserName;
  }

  /**
   * Function calls the postcodeanywhere web service to load a list of addresses
   * registered at the given postcode.
   */
  function MakeRequest() {
    $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByPostcode/v1.00/xmla.ws?";
    $url .= "&Key=" . urlencode($this->Key);
    $url .= "&Postcode=" . urlencode($this->Postcode);
    $url .= "&UserName=" . urlencode($this->UserName);

    // Make the request to Postcode Anywhere and parse the XML returned.
    $file = simplexml_load_file($url);

    // Check for an error, if there is one then throw an exception.
    if ($file->Columns->Column->attributes()->Name == "Error") {
      throw new Exception(
        "[ID] " . $file->Rows->Row->attributes()->Error .
        " [DESCRIPTION] " . $file->Rows->Row->attributes()->Description .
        " [CAUSE] " . $file->Rows->Row->attributes()->Cause .
        " [RESOLUTION] " . $file->Rows->Row->attributes()->Resolution
      );
    }

    // Copy the data
    if (!empty($file->Rows)) {
      foreach ($file->Rows->Row as $item) {
        $this->Data[] = array(
            'Id' => (string)$item->attributes()->Id,
            'StreetAddress' => (string)$item->attributes()->StreetAddress,
            'Place' => (string)$item->attributes()->Place);
      }
    }
  }

  /**
   * Returns the data collected by this instance.
   */
  function HasData() {
    if (!empty($this->Data)) {
      return $this->Data;
    }
    return false;
  }
}

// Example usage
// -------------
// $pa = new PostcodeAnywhere_Interactive_FindByPostcode_v1_00 ("AA11-AA11-AA11-AA11","WR2 6NJ","David");
// $pa->MakeRequest();
// if ($pa->HasData())
// {
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["Id"] . "<br/>";
//      echo $item["StreetAddress"] . "<br/>";
//      echo $item["Place"] . "<br/>";
//   }
// }

/**
 *  This class manages loading the full, specific details of an address selected
 *  by it's uniqued ID. 
 */
class PostcodeAnywhere_Interactive_RetrieveById_v1_20 {

  // Includes country name based on postcode area and the thoroughfare name components.
  // Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

  private $Key;                // The key to use to authenticate to the service.
  private $Id;                 // The Id from a Find method to retrieve the details for.
  private $PreferredLanguage;  // The language version of the address to return.
  private $UserName;           // The username associated with the Royal Mail license (not required for click licenses).
  private $Data;               // Holds the results of the query.

  function PostcodeAnywhere_Interactive_RetrieveById_v1_20($Key, $Id, $PreferredLanguage, $UserName) {
    $this->Key = $Key;
    $this->Id = $Id;
    $this->PreferredLanguage = $PreferredLanguage;
    $this->UserName = $UserName;
  }

  function MakeRequest() {
    $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/RetrieveById/v1.20/xmla.ws?";
    $url .= "&Key=" . urlencode($this->Key);
    $url .= "&Id=" . urlencode($this->Id);
    $url .= "&PreferredLanguage=" . urlencode($this->PreferredLanguage);
    $url .= "&UserName=" . urlencode($this->UserName);

    // Make the request to Postcode Anywhere and parse the XML returned.
    $file = simplexml_load_file($url);

    // Check for an error, if there is one then throw an exception.
    if ($file->Columns->Column->attributes()->Name == "Error") {
      throw new Exception(
           "[ID] " . $file->Rows->Row->attributes()->Error . 
           " [DESCRIPTION] " . $file->Rows->Row->attributes()->Description . 
           " [CAUSE] " . $file->Rows->Row->attributes()->Cause . 
           " [RESOLUTION] " . $file->Rows->Row->attributes()->Resolution
      );
    }

    // Copy the data.
    if (!empty($file->Rows)) {
      foreach ($file->Rows->Row as $item) {
        $this->Data[] = array(
               'Udprn' => (string)$item->attributes()->Udprn,
               'Company' => (string)$item->attributes()->Company,
               'Department' => (string)$item->attributes()->Department,
               'Line1' => (string)$item->attributes()->Line1,
               'Line2' => (string)$item->attributes()->Line2,
               'Line3' => (string)$item->attributes()->Line3,
               'Line4' => (string)$item->attributes()->Line4,
               'Line5' => (string)$item->attributes()->Line5,
               'PostTown' => (string)$item->attributes()->PostTown,
               'County' => (string)$item->attributes()->County,
               'Postcode' => (string)$item->attributes()->Postcode,
               'Mailsort' => (string)$item->attributes()->Mailsort,
               'Barcode' => (string)$item->attributes()->Barcode,
               'Type' => (string)$item->attributes()->Type,
               'DeliveryPointSuffix' => (string)$item->attributes()->DeliveryPointSuffix,
               'SubBuilding' => (string)$item->attributes()->SubBuilding,
               'BuildingName' => (string)$item->attributes()->BuildingName,
               'BuildingNumber' => (string)$item->attributes()->BuildingNumber,
               'PrimaryStreet' => (string)$item->attributes()->PrimaryStreet,
               'SecondaryStreet' => (string)$item->attributes()->SecondaryStreet,
               'DoubleDependentLocality' => (string)$item->attributes()->DoubleDependentLocality,
               'DependentLocality' => (string)$item->attributes()->DependentLocality,
               'PoBox' => (string)$item->attributes()->PoBox,
               'PrimaryStreetName' => (string)$item->attributes()->PrimaryStreetName,
               'PrimaryStreetType' => (string)$item->attributes()->PrimaryStreetType,
               'SecondaryStreetName' => (string)$item->attributes()->SecondaryStreetName,
               'SecondaryStreetType' => (string)$item->attributes()->SecondaryStreetType,
               'CountryName' => (string)$item->attributes()->CountryName
        );
      }
    }
  }

  function HasData() {
    if (!empty($this->Data)) {
      return $this->Data;
    }
    return false;
  }

}

// Example usage
// -------------
// $pa = new PostcodeAnywhere_Interactive_RetrieveById_v1_20 ("AA11-AA11-AA11-AA11","23747212.00","English","David");
// $pa->MakeRequest();
// if ($pa->HasData())
// {
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["Udprn"] . "<br/>";
//      echo $item["Company"] . "<br/>";
//      echo $item["Department"] . "<br/>";
//      echo $item["Line1"] . "<br/>";
//      echo $item["Line2"] . "<br/>";
//      echo $item["Line3"] . "<br/>";
//      echo $item["Line4"] . "<br/>";
//      echo $item["Line5"] . "<br/>";
//      echo $item["PostTown"] . "<br/>";
//      echo $item["County"] . "<br/>";
//      echo $item["Postcode"] . "<br/>";
//      echo $item["Mailsort"] . "<br/>";
//      echo $item["Barcode"] . "<br/>";
//      echo $item["Type"] . "<br/>";
//      echo $item["DeliveryPointSuffix"] . "<br/>";
//      echo $item["SubBuilding"] . "<br/>";
//      echo $item["BuildingName"] . "<br/>";
//      echo $item["BuildingNumber"] . "<br/>";
//      echo $item["PrimaryStreet"] . "<br/>";
//      echo $item["SecondaryStreet"] . "<br/>";
//      echo $item["DoubleDependentLocality"] . "<br/>";
//      echo $item["DependentLocality"] . "<br/>";
//      echo $item["PoBox"] . "<br/>";
//      echo $item["PrimaryStreetName"] . "<br/>";
//      echo $item["PrimaryStreetType"] . "<br/>";
//      echo $item["SecondaryStreetName"] . "<br/>";
//      echo $item["SecondaryStreetType"] . "<br/>";
//      echo $item["CountryName"] . "<br/>";
//   }
// }
