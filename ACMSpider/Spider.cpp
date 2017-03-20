#include "stdafx.h"
#include "Spider.h"
#include "curl/curl.h"
#include <regex>

#pragma comment(lib,"libcurl")

/*
* д��ص�����
*/
size_t curl_callback_write(char * __ptr, size_t __size, size_t __buffsize, std::string * __usr)
{
	__usr->append(__ptr);
	return __size * __buffsize;
}

/*
 * ʹ��Ĭ�ϲ���ֵ��http����ͷ��ʼ��curl
 */
CURL * init_curl(CURL * __curl)
{
	if (__curl)
		curl_easy_cleanup(__curl);
	__curl = curl_easy_init();
	// ����cookie
	curl_easy_setopt(__curl, CURLOPT_COOKIEJAR, "cookie.txt");
	curl_easy_setopt(__curl, CURLOPT_COOKIEFILE, "cookie.txt");
	// ����http����ͷ
	curl_slist * header{};
	header = curl_slist_append(header, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87");
	header = curl_slist_append(header, "Referer: http://acm.sdut.edu.cn/onlinejudge2/index.php/Home/Login/login");
	curl_easy_setopt(__curl, CURLOPT_HTTPHEADER, header);
	// ��������
	curl_easy_setopt(__curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(__curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(__curl, CURLOPT_RANGE, "0-204800");
	return __curl;
}

/*
 * ��������ȡ��ҳ
 */
std::string get_html(const char * __url)
{
	if (!__url)
		return std::string{ "null" };
	CURL * curl{};
	curl = init_curl(curl);
	curl_easy_setopt(curl, CURLOPT_URL, __url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback_write);
	std::string ret;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return ret;
}

/*
 * ģ���¼
 */
bool login_acm(const std::string & __username, const std::string & __pwd)
{
	// ����post����
	CURL * login{};
	login = init_curl(login);
	curl_easy_setopt(login, CURLOPT_URL, "http://acm.sdut.edu.cn/onlinejudge2/index.php/Home/Login/login");
	curl_easy_setopt(login, CURLOPT_POST, 1);
	std::string post{ "user_name=" + __username + "&password=" + __pwd };
	curl_easy_setopt(login, CURLOPT_POSTFIELDS, post.c_str());
	curl_easy_setopt(login, CURLOPT_WRITEFUNCTION, curl_callback_write);
	std::string html;
	curl_easy_setopt(login, CURLOPT_WRITEDATA, &html);
	curl_easy_perform(login);
	curl_easy_cleanup(login);
	return html.find("��¼ʧ��") == std::string::npos ? true : false;
}

/*
 * ��ȡ��Ŀcid��pid
 */
bool get_problem_pid_cid(const char * __url,std::string & __pid,std::string & __cid)
{
	// ��������: http://acm.sdut.edu.cn/onlinejudge2/index.php/Home/Contest/contestproblem/cid/2038/pid/1000
	std::string url{ __url };
	auto nCidStart{ url.find("cid/") };
	auto nPidStart{ url.find("pid/") };
	if (nCidStart == std::string::npos || nPidStart == std::string::npos)
		return false;
	__pid = url.substr(nPidStart + 4, 4);
	__cid = url.substr(nCidStart + 4, 4);
	return true;
}

/*
 * ת��HTML�ַ�
 */
std::string remove_html(std::string __code)
{
	char * ret = new char[__code.size() + 1];
	*regex_replace(ret, __code.begin(), __code.end(), std::regex{ "&quot;" }, "\"") = '\0';
	*regex_replace(ret, ret, ret + strlen(ret), std::regex{ "&lt;" }, "<") = '\0';
	*regex_replace(ret, ret, ret + strlen(ret), std::regex{ "&gt;" }, ">") = '\0';
	*regex_replace(ret, ret, ret + strlen(ret), std::regex{ "&amp;" }, "&") = '\0';
	*regex_replace(ret, ret, ret + strlen(ret), std::regex{ "&#039;" }, "'") = '\0';
	return ret;
}

/*
 * ��ȡ����
 */
bool get_code(std::string  __url , std::string & __code)
{
	std::string url{ "http://acm.sdut.edu.cn" + __url };
	std::string html{ get_html(url.c_str()) };
	std::regex regex{ "<pre class=\"brush:[^\\s]{3,7};\">([\\w\\W]*)</pre>" };
	std::smatch match;
	if(regex_search(html, match, regex))
	{
		std::string tmp{ match.begin()->str() };
		auto codeStart = tmp.find(">") + 1;
		auto codeEnd = tmp.find("/****");
		__code = remove_html(tmp.substr(codeStart, codeEnd - codeStart));
		return true;
	}
	return false;
}

/*
 * ���Ҵ���
 */
bool get_submit_code(const char * __url, std::string & __code, std::string & __lang, int & __page)
{
	// ���Ȼ�ȡpid��cid
	std::string pid;
	std::string cid;
	if (!get_problem_pid_cid(__url, pid, cid))
		return false;
	const std::string baseURL{
		"http://acm.sdut.edu.cn/onlinejudge2/index.php/Contest/conteststatus/cid/" + cid + "/pid/" + pid + "/result/1/p/"
	};
	// ������Ӧ����һ��baseurl��ȡҳ��͵�һҳ��ƥ����Ϣ
	std::string html{ get_html(baseURL.c_str()) };
	// ��ȡ�ܵ�ҳ��
	std::smatch match;
	std::regex regex("\\d+</a> <a class=\"next\"");
	std::string tmp;
	int nPageNum{};
	if (regex_search(html, match, regex))
	{
		tmp = match.begin()->str();
		sscanf_s(tmp.c_str(), "%d</a> <a class=\"next\"", &nPageNum);
	}
	else
		nPageNum = 1;
	// ����,�����ܵ�ҳ����,һ��һ���Ұ�
	regex = "<td><a href=\"/onlinejudge2/index.php/Home/Viewcode/view/sid/\\d+\">" + __lang + "</a></td>";
	std::string codeURL;
	char * numBuff = new char[3];
	for (int i = 1; i <= nPageNum; i++)
	{
		_itoa_s(i, numBuff, 3, 10);
		codeURL = baseURL + numBuff + ".html";
		html = get_html(codeURL.c_str());
		if(regex_search(html,match,regex))
		{
			tmp = match.begin()->str();
			auto firstqouto = tmp.find("\"");
			auto lastqouto = tmp.find("\"", firstqouto + 1);
			__page = i;
			return get_code(tmp.substr(firstqouto + 1, lastqouto - firstqouto - 1), __code);
		}
	}
	return false;
}
