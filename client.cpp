#include <iostream>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
//Modify Put Method
void modify_put(std::string data) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
    struct curl_slist *headers = NULL;
        // Set the request data to the integer value 1024
        //std::string data = "4";
    
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/modify");
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // Perform the PUT request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup the curl handle
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

}
//Initialize Put Method
void init_put(std::string data) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
	struct curl_slist *headers = NULL;
        // Set the request data to the integer value 3360
	
	headers = curl_slist_append(headers, "Content-Type: application/json");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/initialize");
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // Perform the PUT request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup the curl handle
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}
//Initialize Get Method 
std::string init_get() {  
 
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    std::string temp;
    // Create a new curl handle for the GET request
    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/initialize");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Create a string buffer to hold the response data
        std::string buffer;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	
        // Perform the GET request
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup the curl handle
        curl_easy_cleanup(curl);

        // Print the response body
        //std::cout << "\nResponse body: " << buffer << std::endl;
	temp = buffer;        
    }
    // Cleanup libcurl
    curl_global_cleanup();
    return temp;
}
//Modify Get Method
std::string modify_get() {  
 
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);
    std::string temp;
    // Create a new curl handle for the GET request
    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/modify");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // Create a string buffer to hold the response data
        std::string buffer;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	
        // Perform the GET request
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup the curl handle
        curl_easy_cleanup(curl);

        // Print the response body
	temp = buffer;
        //std::cout << "\nResponse body: " << buffer << std::endl;
        
    }
    // Cleanup libcurl
    curl_global_cleanup();
    return temp;
}
int main() {
    std::string initNum, init2, modNum, mod2;
    //Send the init put
    init_put("3360");
    //store init_get and display it in own line
    initNum = init_get();
    std::cout << std::endl << initNum << std::endl;
    //send the modify put
    modify_put("4");
    //store modify_put and display it in own line
    modNum = modify_get();
    std::cout << std::endl << modNum << std::endl;
    //send the value from /modify to /initialize via PUT.
    std::cout << initNum << std::endl;
    init_put(modNum);
    //send the value from /initialize to /modify via PUT.
    modify_put(initNum);
    init2 = init_get();
    mod2 = modify_get();
    //display new values
    std::cout << init2 << std::endl;
    std::cout << mod2 << std::endl;
    return 0;
}

