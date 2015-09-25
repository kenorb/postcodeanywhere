<?php
/*

  @file
    PostcodeAnywhere Interactive FindByPartialPostcode (v1.00)

  Lists address records for the given partial postcode.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByPartialPostcode/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByPartialPostcode/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByPartialPostcode/v1.00/json.ws?Key=AA11-AA11-AA11-AA11&PartialPostcode=WR2&UserName=David
  Sample response: [{"Id":"30334||WR2","Place":"WR2 Worcester Worcestershire"}, {"Id":"30363||WR2","Place":"WR2 Callow End Worcester Worcestershire"}, {"Id":"32519||WR2","Place":"WR2 Crown East Worcester Worcestershire"}, {"Id":"37181||WR2","Place":"WR2 St. Johns Worcester Worcestershire"}]

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/findbypartialpostcode/1/

*/

class PostcodeAnywhere_Interactive_FindByPartialPostcode
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $PartialPostcode; //The partial postcode to search with find.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_FindByPartialPostcode_v1_00($Key, $PartialPostcode, $UserName)
   {
      $this->Key = $Key;
      $this->PartialPostcode = $PartialPostcode;
      $this->UserName = $UserName;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByPartialPostcode/v1.00/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&PartialPostcode=" . urlencode($this->PartialPostcode);
      $url .= "&UserName=" . urlencode($this->UserName);

      //Make the request to Postcode Anywhere and parse the XML returned
      $file = simplexml_load_file($url);

      //Check for an error, if there is one then throw an exception
      if ($file->Columns->Column->attributes()->Name == "Error") 
      {
         throw new Exception("[ID] " . $file->Rows->Row->attributes()->Error . " [DESCRIPTION] " . $file->Rows->Row->attributes()->Description . " [CAUSE] " . $file->Rows->Row->attributes()->Cause . " [RESOLUTION] " . $file->Rows->Row->attributes()->Resolution);
      }

      //Copy the data
      if ( !empty($file->Rows) )
      {
         foreach ($file->Rows->Row as $item)
         {
             $this->Data[] = array('Id'=>$item->attributes()->Id,'Place'=>$item->attributes()->Place);
         }
      }
   }

   function HasData()
   {
      if ( !empty($this->Data) )
      {
         return $this->Data;
      }
      return false;
   }

}

//Example usage
//-------------
//$pa = new PostcodeAnywhere_Interactive_FindByPartialPostcode_v1_00 ("AA11-AA11-AA11-AA11","WR2","David");
//$pa->MakeRequest();
//if ($pa->HasData())
//{
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["Id"] . "<br/>";
//      echo $item["Place"] . "<br/>";
//   }
//}

