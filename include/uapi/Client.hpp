#pragma once
#include <string>
#include <stdexcept>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cctype>

#ifdef _WIN32
#  include <windows.h>
#  include <winhttp.h>
#  pragma comment(lib, "winhttp.lib")
#else
#  include <cstdio>
#endif

namespace uapi {

struct UapiError: public std::runtime_error {
    std::string code;
    int status;
    UapiError(std::string c, int s, std::string msg): std::runtime_error("["+std::to_string(s)+"] "+c+": "+msg), code(std::move(c)), status(s) {}
};
struct ApiErrorError: public UapiError { using UapiError::UapiError; };
struct AvatarNotFoundError: public UapiError { using UapiError::UapiError; };
struct ConversionFailedError: public UapiError { using UapiError::UapiError; };
struct FileOpenErrorError: public UapiError { using UapiError::UapiError; };
struct FileRequiredError: public UapiError { using UapiError::UapiError; };
struct InternalServerErrorError: public UapiError { using UapiError::UapiError; };
struct InvalidParameterError: public UapiError { using UapiError::UapiError; };
struct InvalidParamsError: public UapiError { using UapiError::UapiError; };
struct NotFoundError: public UapiError { using UapiError::UapiError; };
struct NoMatchError: public UapiError { using UapiError::UapiError; };
struct NoTrackingDataError: public UapiError { using UapiError::UapiError; };
struct PhoneInfoFailedError: public UapiError { using UapiError::UapiError; };
struct RecognitionFailedError: public UapiError { using UapiError::UapiError; };
struct RequestEntityTooLargeError: public UapiError { using UapiError::UapiError; };
struct ServiceBusyError: public UapiError { using UapiError::UapiError; };
struct TimezoneNotFoundError: public UapiError { using UapiError::UapiError; };
struct UnauthorizedError: public UapiError { using UapiError::UapiError; };
struct UnsupportedCarrierError: public UapiError { using UapiError::UapiError; };
struct UnsupportedFormatError: public UapiError { using UapiError::UapiError; };

class Client {
public:
    Client(std::string baseUrl = "https://uapis.cn/api/v1", std::string tok = "");
    struct ClipzyZaiXianJianTieBanApi {
        Client* c;
        explicit ClipzyZaiXianJianTieBanApi(Client* cli): c(cli) {}
        std::string getClipzyGet(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/api/get";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getClipzyRaw(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/api/raw/{id}";
            if (auto it = args.find("id"); it != args.end()) { auto ph = std::string("{") + "id" + "}"; auto pos = path.find(ph); if (pos!=std::string::npos) path.replace(pos, ph.size(), it->second); }
            auto query = args;
            if (auto it = query.find("id"); it != query.end()) query.erase(it);
            return c->request("GET", path, query);
        }
        std::string postClipzyStore(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/api/store";
            auto query = args;
            return c->request("POST", path, query);
        }
    };
    ClipzyZaiXianJianTieBanApi clipzyZaiXianJianTieBan() { return ClipzyZaiXianJianTieBanApi(this); }
    struct ConvertApi {
        Client* c;
        explicit ConvertApi(Client* cli): c(cli) {}
        std::string getConvertUnixtime(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/convert/unixtime";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string postConvertJson(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/convert/json";
            auto query = args;
            return c->request("POST", path, query);
        }
    };
    ConvertApi convert() { return ConvertApi(this); }
    struct DailyApi {
        Client* c;
        explicit DailyApi(Client* cli): c(cli) {}
        std::string getDailyNewsImage(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/daily/news-image";
            auto query = args;
            return c->request("GET", path, query);
        }
    };
    DailyApi daily() { return DailyApi(this); }
    struct GameApi {
        Client* c;
        explicit GameApi(Client* cli): c(cli) {}
        std::string getGameEpicFree(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/epic-free";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getGameMinecraftHistoryid(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/minecraft/historyid";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getGameMinecraftServerstatus(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/minecraft/serverstatus";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getGameMinecraftUserinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/minecraft/userinfo";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getGameSteamSummary(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/steam/summary";
            auto query = args;
            return c->request("GET", path, query);
        }
    };
    GameApi game() { return GameApi(this); }
    struct ImageApi {
        Client* c;
        explicit ImageApi(Client* cli): c(cli) {}
        std::string getAvatarGravatar(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/avatar/gravatar";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getImageBingDaily(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/bing-daily";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getImageMotou(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/motou";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getImageQrcode(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/qrcode";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getImageTobase64(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/tobase64";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string postImageCompress(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/compress";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postImageFrombase64(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/frombase64";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postImageMotou(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/motou";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postImageSpeechless(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/speechless";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postImageSvg(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/svg";
            auto query = args;
            return c->request("POST", path, query);
        }
    };
    ImageApi image() { return ImageApi(this); }
    struct MiscApi {
        Client* c;
        explicit MiscApi(Client* cli): c(cli) {}
        std::string getHistoryProgrammer(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/history/programmer";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getHistoryProgrammerToday(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/history/programmer/today";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getMiscHotboard(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/hotboard";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getMiscPhoneinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/phoneinfo";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getMiscRandomnumber(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/randomnumber";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getMiscTimestamp(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/timestamp";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getMiscTrackingCarriers(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/tracking/carriers";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getMiscTrackingDetect(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/tracking/detect";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getMiscTrackingQuery(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/tracking/query";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getMiscWeather(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/weather";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getMiscWorldtime(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/worldtime";
            auto query = args;
            return c->request("GET", path, query);
        }
    };
    MiscApi misc() { return MiscApi(this); }
    struct NetworkApi {
        Client* c;
        explicit NetworkApi(Client* cli): c(cli) {}
        std::string getNetworkDns(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/dns";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getNetworkIcp(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/icp";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getNetworkIpinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/ipinfo";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getNetworkMyip(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/myip";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getNetworkPing(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/ping";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getNetworkPingmyip(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/pingmyip";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getNetworkPortscan(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/portscan";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getNetworkUrlstatus(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/urlstatus";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getNetworkWhois(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/whois";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getNetworkWxdomain(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/wxdomain";
            auto query = args;
            return c->request("GET", path, query);
        }
    };
    NetworkApi network() { return NetworkApi(this); }
    struct PoemApi {
        Client* c;
        explicit PoemApi(Client* cli): c(cli) {}
        std::string getSaying(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/saying";
            auto query = args;
            return c->request("GET", path, query);
        }
    };
    PoemApi poem() { return PoemApi(this); }
    struct RandomApi {
        Client* c;
        explicit RandomApi(Client* cli): c(cli) {}
        std::string getAnswerbookAsk(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/answerbook/ask";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getRandomImage(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/random/image";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getRandomString(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/random/string";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string postAnswerbookAsk(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/answerbook/ask";
            auto query = args;
            return c->request("POST", path, query);
        }
    };
    RandomApi random() { return RandomApi(this); }
    struct SocialApi {
        Client* c;
        explicit SocialApi(Client* cli): c(cli) {}
        std::string getGithubRepo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/github/repo";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getSocialBilibiliArchives(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/archives";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getSocialBilibiliLiveroom(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/liveroom";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getSocialBilibiliReplies(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/replies";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getSocialBilibiliUserinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/userinfo";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getSocialBilibiliVideoinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/videoinfo";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getSocialQqGroupinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/qq/groupinfo";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getSocialQqUserinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/qq/userinfo";
            auto query = args;
            return c->request("GET", path, query);
        }
    };
    SocialApi social() { return SocialApi(this); }
    struct StatusApi {
        Client* c;
        explicit StatusApi(Client* cli): c(cli) {}
        std::string getStatusRatelimit(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/status/ratelimit";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getStatusUsage(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/status/usage";
            auto query = args;
            return c->request("GET", path, query);
        }
    };
    StatusApi status() { return StatusApi(this); }
    struct TextApi {
        Client* c;
        explicit TextApi(Client* cli): c(cli) {}
        std::string getTextMd5(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/md5";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string postTextAesDecrypt(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/aes/decrypt";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postTextAesEncrypt(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/aes/encrypt";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postTextAnalyze(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/analyze";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postTextBase64Decode(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/base64/decode";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postTextBase64Encode(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/base64/encode";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postTextMd5(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/md5";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postTextMd5Verify(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/md5/verify";
            auto query = args;
            return c->request("POST", path, query);
        }
    };
    TextApi text() { return TextApi(this); }
    struct TranslateApi {
        Client* c;
        explicit TranslateApi(Client* cli): c(cli) {}
        std::string getAiTranslateLanguages(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/ai/translate/languages";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string postAiTranslate(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/ai/translate";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postTranslateStream(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/translate/stream";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postTranslateText(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/translate/text";
            auto query = args;
            return c->request("POST", path, query);
        }
    };
    TranslateApi translate() { return TranslateApi(this); }
    struct WebparseApi {
        Client* c;
        explicit WebparseApi(Client* cli): c(cli) {}
        std::string getWebTomarkdownAsyncStatus(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/web/tomarkdown/async/{task_id}";
            if (auto it = args.find("task_id"); it != args.end()) { auto ph = std::string("{") + "task_id" + "}"; auto pos = path.find(ph); if (pos!=std::string::npos) path.replace(pos, ph.size(), it->second); }
            auto query = args;
            if (auto it = query.find("task_id"); it != query.end()) query.erase(it);
            return c->request("GET", path, query);
        }
        std::string getWebparseExtractimages(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/webparse/extractimages";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string getWebparseMetadata(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/webparse/metadata";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string postWebTomarkdownAsync(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/web/tomarkdown/async";
            auto query = args;
            return c->request("POST", path, query);
        }
    };
    WebparseApi webparse() { return WebparseApi(this); }
    struct MinGanCiShiBieApi {
        Client* c;
        explicit MinGanCiShiBieApi(Client* cli): c(cli) {}
        std::string getSensitiveWordAnalyzeQuery(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/sensitive-word/analyze-query";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string postSensitiveWordAnalyze(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/sensitive-word/analyze";
            auto query = args;
            return c->request("POST", path, query);
        }
        std::string postSensitiveWordQuickCheck(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/profanitycheck";
            auto query = args;
            return c->request("POST", path, query);
        }
    };
    MinGanCiShiBieApi minGanCiShiBie() { return MinGanCiShiBieApi(this); }
    struct ZhiNengSouSuoApi {
        Client* c;
        explicit ZhiNengSouSuoApi(Client* cli): c(cli) {}
        std::string getSearchEngines(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/search/engines";
            auto query = args;
            return c->request("GET", path, query);
        }
        std::string postSearchAggregate(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/search/aggregate";
            auto query = args;
            return c->request("POST", path, query);
        }
    };
    ZhiNengSouSuoApi zhiNengSouSuo() { return ZhiNengSouSuoApi(this); }

private:
    std::string origin;
    std::string host;
    std::string basePath;
    unsigned short port;
    bool secure;
    std::string token;

    std::string request(const std::string& method, std::string path, const std::map<std::string, std::string>& query) const;
    std::string buildQuery(const std::map<std::string, std::string>& query) const;
    static std::string urlEncode(const std::string& value);
    std::string defaultCode(int status) const;
    void raiseError(int status, const std::string& body) const;
    static std::string extractField(const std::string& body, const std::string& key);
#ifdef _WIN32
    std::string sendWinHttp(const std::string& method, const std::string& pathAndQuery) const;
    static std::wstring widen(const std::string& input);
#else
    std::string sendCurl(const std::string& method, const std::string& absoluteUrl) const;
    static std::string shellEscape(const std::string& value);
#endif
};

inline Client::Client(std::string baseUrl, std::string tok): host(), basePath("/"), port(443), secure(true), token(std::move(tok)) {
    if (baseUrl.empty()) baseUrl = "https://uapis.cn/api/v1";
    auto schemePos = baseUrl.find("://");
    std::string scheme = schemePos == std::string::npos ? "https" : baseUrl.substr(0, schemePos);
    secure = (scheme == "https");
    std::string rest = schemePos == std::string::npos ? baseUrl : baseUrl.substr(schemePos + 3);
    auto slashPos = rest.find('/');
    host = slashPos == std::string::npos ? rest : rest.substr(0, slashPos);
    basePath = slashPos == std::string::npos ? "/" : rest.substr(slashPos);
    if (basePath.empty()) basePath = "/";
    if (basePath.back() != '/') basePath.push_back('/');
    auto colonPos = host.find(':');
    if (colonPos != std::string::npos) {
        port = static_cast<unsigned short>(std::stoi(host.substr(colonPos + 1)));
        host = host.substr(0, colonPos);
    } else {
        port = secure ? 443 : 80;
    }
    origin = std::string(secure ? "https://" : "http://") + host;
    if (!(secure && port == 443) && !(!secure && port == 80)) {
        origin += ":" + std::to_string(port);
    }
}

inline std::string Client::request(const std::string& method, std::string path, const std::map<std::string, std::string>& query) const {
    if (!path.empty() && path.front() == '/') path.erase(0, 1);
    std::string normalized = basePath;
    if (!normalized.empty() && normalized.back() == '/' && !path.empty()) {
        normalized += path;
    } else if (!path.empty()) {
        if (!normalized.empty() && normalized.back() != '/') normalized.push_back('/');
        normalized += path;
    }
    if (normalized.empty()) normalized = "/";
    auto queryString = buildQuery(query);
#ifdef _WIN32
    return sendWinHttp(method, normalized + queryString);
#else
    return sendCurl(method, origin + normalized + queryString);
#endif
}

inline std::string Client::buildQuery(const std::map<std::string, std::string>& query) const {
    if (query.empty()) return {};
    std::string out;
    bool first = true;
    for (const auto& kv : query) {
        out += first ? '?' : '&';
        first = false;
        out += urlEncode(kv.first);
        out += '=';
        out += urlEncode(kv.second);
    }
    return out;
}

inline std::string Client::urlEncode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex << std::uppercase;
    for (unsigned char c : value) {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << std::setw(2) << int(c);
            escaped << std::nouppercase;
        }
    }
    return escaped.str();
}

inline std::string Client::defaultCode(int status) const {
    if (status == 401 || status == 403) return "UNAUTHORIZED";
    if (status == 404) return "NOT_FOUND";
    if (status == 429) return "SERVICE_BUSY";
    if (status >= 500) return "INTERNAL_SERVER_ERROR";
    if (status >= 400) return "API_ERROR";
    return "OK";
}

inline std::string Client::extractField(const std::string& body, const std::string& key) {
    auto keyPos = body.find("\"" + key + "\"");
    if (keyPos == std::string::npos) return {};
    auto colon = body.find(':', keyPos);
    if (colon == std::string::npos) return {};
    auto quoteStart = body.find_first_of("\"'", colon + 1);
    if (quoteStart == std::string::npos) return {};
    char q = body[quoteStart];
    auto quoteEnd = body.find(q, quoteStart + 1);
    if (quoteEnd == std::string::npos) return {};
    return body.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
}

inline void Client::raiseError(int status, const std::string& body) const {
    std::string code = extractField(body, "code");
    if (code.empty()) code = defaultCode(status);
    std::string message = extractField(body, "message");
    if (message.empty()) message = "HTTP " + std::to_string(status);
    if (false) {}
    else if (code == "API_ERROR") throw ApiErrorError(code, status, message);
    else if (code == "AVATAR_NOT_FOUND") throw AvatarNotFoundError(code, status, message);
    else if (code == "CONVERSION_FAILED") throw ConversionFailedError(code, status, message);
    else if (code == "FILE_OPEN_ERROR") throw FileOpenErrorError(code, status, message);
    else if (code == "FILE_REQUIRED") throw FileRequiredError(code, status, message);
    else if (code == "INTERNAL_SERVER_ERROR") throw InternalServerErrorError(code, status, message);
    else if (code == "INVALID_PARAMETER") throw InvalidParameterError(code, status, message);
    else if (code == "INVALID_PARAMS") throw InvalidParamsError(code, status, message);
    else if (code == "NOT_FOUND") throw NotFoundError(code, status, message);
    else if (code == "NO_MATCH") throw NoMatchError(code, status, message);
    else if (code == "NO_TRACKING_DATA") throw NoTrackingDataError(code, status, message);
    else if (code == "PHONE_INFO_FAILED") throw PhoneInfoFailedError(code, status, message);
    else if (code == "RECOGNITION_FAILED") throw RecognitionFailedError(code, status, message);
    else if (code == "REQUEST_ENTITY_TOO_LARGE") throw RequestEntityTooLargeError(code, status, message);
    else if (code == "SERVICE_BUSY") throw ServiceBusyError(code, status, message);
    else if (code == "TIMEZONE_NOT_FOUND") throw TimezoneNotFoundError(code, status, message);
    else if (code == "UNAUTHORIZED") throw UnauthorizedError(code, status, message);
    else if (code == "UNSUPPORTED_CARRIER") throw UnsupportedCarrierError(code, status, message);
    else if (code == "UNSUPPORTED_FORMAT") throw UnsupportedFormatError(code, status, message);
    else throw UapiError(code, status, message);
}

#ifdef _WIN32
inline std::wstring Client::widen(const std::string& input) {
    if (input.empty()) return {};
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), nullptr, 0);
    std::wstring wide(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), wide.data(), size_needed);
    return wide;
}

inline std::string Client::sendWinHttp(const std::string& method, const std::string& pathAndQuery) const {
    auto hSession = WinHttpOpen(L"uapi-sdk-cpp/0.1.2", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!hSession) throw std::runtime_error("WinHttpOpen failed");
    auto closeSession = [&]() { if (hSession) WinHttpCloseHandle(hSession); hSession = nullptr; };
    std::string result;
    HINTERNET hConnect = WinHttpConnect(hSession, widen(host).c_str(), port, 0);
    if (!hConnect) { closeSession(); throw std::runtime_error("WinHttpConnect failed"); }
    auto closeConnect = [&]() { if (hConnect) WinHttpCloseHandle(hConnect); hConnect = nullptr; };
    DWORD flags = secure ? WINHTTP_FLAG_SECURE : 0;
    HINTERNET hRequest = WinHttpOpenRequest(hConnect, widen(method).c_str(), widen(pathAndQuery).c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, flags);
    if (!hRequest) { closeConnect(); closeSession(); throw std::runtime_error("WinHttpOpenRequest failed"); }

    std::wstring headers = L"Accept: application/json\r\n";
    if (!token.empty()) headers += L"Authorization: Bearer " + widen(token) + L"\r\n";
    if (!WinHttpSendRequest(hRequest, headers.c_str(), static_cast<DWORD>(headers.length()), WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
        WinHttpCloseHandle(hRequest); closeConnect(); closeSession();
        throw std::runtime_error("WinHttpSendRequest failed");
    }
    if (!WinHttpReceiveResponse(hRequest, nullptr)) {
        WinHttpCloseHandle(hRequest); closeConnect(); closeSession();
        throw std::runtime_error("WinHttpReceiveResponse failed");
    }
    DWORD status = 0;
    DWORD statusLen = sizeof(status);
    WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &status, &statusLen, WINHTTP_NO_HEADER_INDEX);
    DWORD available = 0;
    do {
        if (!WinHttpQueryDataAvailable(hRequest, &available)) break;
        if (!available) break;
        std::string buffer(available, '\0');
        DWORD read = 0;
        if (!WinHttpReadData(hRequest, buffer.data(), available, &read)) break;
        result.append(buffer.c_str(), read);
    } while (available > 0);
    WinHttpCloseHandle(hRequest);
    closeConnect();
    closeSession();
    if (status >= 400) {
        raiseError(static_cast<int>(status), result);
    }
    return result;
}
#else
inline std::string Client::shellEscape(const std::string& value) {
    std::string escaped = "'";
    for (char c : value) {
        if (c == '\'') escaped += "'\\''";
        else escaped.push_back(c);
    }
    escaped += "'";
    return escaped;
}

inline std::string Client::sendCurl(const std::string& method, const std::string& absoluteUrl) const {
    std::string cmd = "curl -s -S -w \"\\n%{http_code}\" -X " + method + " " + shellEscape(absoluteUrl) + " -H \"Accept: application/json\"";
    if (!token.empty()) cmd += " -H " + shellEscape("Authorization: Bearer " + token);
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) throw std::runtime_error("failed to start curl");
    std::string output;
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output += buffer;
    }
    int rc = pclose(pipe);
    (void)rc;
    auto pos = output.find_last_of('\n');
    if (pos == std::string::npos) throw std::runtime_error("unexpected curl output");
    std::string body = output.substr(0, pos);
    std::string statusLine = output.substr(pos + 1);
    int status = std::stoi(statusLine);
    if (status >= 400) {
        raiseError(status, body);
    }
    return body;
}
#endif

} // namespace
