<?php
/*

  @file
    PostcodeAnywhere Interactive FindByAreaId (v1.00)

  Lists localities in a given postcode area.
  SOAP WSDL
  Standard HTTP
  http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByAreaId/v1.00/wsdlnew.ws
  Secure HTTPS
  https://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByAreaId/v1.00/wsdlnew.ws

  Sample request: http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByAreaId/v1.00/json.ws?Key=AA11-AA11-AA11-AA11&PostcodeArea=WR&UserName=David
  Sample response: [{"Id":"29984","Place":"Broadway Worcestershire"}, "Id":"90333","Place":"Little Clevelode Malvern Worcestershire"}, {"Id":"90359","Place":"Sneachill Worcester Worcestershire"}, {"Id":"90670","Place":"Iron Cross Salford Priors Evesham Warwickshire"}, {"Id":"91392","Place":"Ryall Upton-upon-Severn Worcester Worcestershire"}]

  Demo: http://www.pcapredict.com/support/webservice/postcodeanywhere/interactive/findbyareaid/1/

*/

class PostcodeAnywhere_Interactive_FindByAreaId
{

   //Credit: Thanks to Stuart Sillitoe (http://stu.so/me) for the original PHP that these samples are based on.

   private $Key; //The key to use to authenticate to the service.
   private $PostcodeArea; //The postcode area to search with.
   private $UserName; //The username associated with the Royal Mail license (not required for click licenses).
   private $Data; //Holds the results of the query

   function PostcodeAnywhere_Interactive_FindByAreaId($Key, $PostcodeArea, $UserName)
   {
      $this->Key = $Key;
      $this->PostcodeArea = $PostcodeArea;
      $this->UserName = $UserName;
   }

   function MakeRequest()
   {
      $url = "http://services.postcodeanywhere.co.uk/PostcodeAnywhere/Interactive/FindByAreaId/v1.00/xmla.ws?";
      $url .= "&Key=" . urlencode($this->Key);
      $url .= "&PostcodeArea=" . urlencode($this->PostcodeArea);
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
//$pa = new PostcodeAnywhere_Interactive_FindByAreaId_v1_00 ("AA11-AA11-AA11-AA11","WR","David");
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

