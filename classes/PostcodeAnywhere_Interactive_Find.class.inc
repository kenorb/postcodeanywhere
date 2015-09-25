<?php

/*

  @file
    PostcodeAnywhere Interactive Find

  Lists address records matching the specified search term. This general search method can search by postcode, company or street.

  Includes support for Welsh alternative addresses when searching by postcode and output filtering
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/Find/v1.10/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/Find/v1.10/wsdlnew.ws

  Example request:
    http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/Find/v1.10/json.ws?Key=AA11-AA11-AA11-AA11&SearchTerm=LL11 5HJ&PreferredLanguage=English&Filter=None&UserName=David

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/find/1.1/

*/

class PostcodeAnywhere_Interactive_Find
{

   //Includes support for Welsh alternative addresses when searching by postcode and output filtering
   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $SearchTerm; //The search term to find. The search term can be a postcode, company name or street and town (separated by commas).
   private $PreferredLanguage; //The language version of the address to return.
   private $Filter; //The filter to apply to the output.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_Find_v1_10($Key, $SearchTerm, $PreferredLanguage, $Filter, $UserName)
   {
      $this->Key = $Key;
      $this->SearchTerm = $SearchTerm;
      $this->PreferredLanguage = $PreferredLanguage;
      $this->Filter = $Filter;
      $this->UserName = $UserName;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/Find/v1.10/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&SearchTerm=" . urlencode($this->SearchTerm);
      $url .= "&PreferredLanguage=" . urlencode($this->PreferredLanguage);
      $url .= "&Filter=" . urlencode($this->Filter);
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
             $this->Data[] = array('Id'=>$item->attributes()->Id,'StreetAddress'=>$item->attributes()->StreetAddress,'Place'=>$item->attributes()->Place);
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
//$pa = new PostcodeAnywhere_Interactive_Find_v1_10 ("AA11-AA11-AA11-AA11","LL11 5HJ","English","None","David");
//$pa->MakeRequest();
//if ($pa->HasData())
//{
//   $data = $pa->HasData();
//   foreach ($data as $item)
//   {
//      echo $item["Id"] . "<br/>";
//      echo $item["StreetAddress"] . "<br/>";
//      echo $item["Place"] . "<br/>";
//   }
//}
