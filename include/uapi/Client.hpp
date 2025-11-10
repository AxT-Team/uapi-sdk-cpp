#pragma once
#include <string>
#include <stdexcept>
#include <map>

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
    std::string base;
    std::string token;
public:
    Client(std::string baseUrl, std::string tok = ""): base(std::move(baseUrl)), token(std::move(tok)) {}

    // 这里演示接口；实际 HTTP 实现在 internal/ 中由 openapi-generator 提供或由用户集成
    // 为保证跨平台与简单性，此处仅给出方法签名与错误模型。
    struct ClipzyZaiXianJianTieBanApi {
        Client* c;
        ClipzyZaiXianJianTieBanApi(Client* cli): c(cli) {}
        std::string getClipzyGet(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/api/get";
            return std::string("GET ") + path;
        }
        std::string getClipzyRaw(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/api/raw/{id}";
            if (auto it = args.find("id"); it != args.end()) { auto ph = std::string("{") + "id" + "}"; auto pos = path.find(ph); if (pos!=std::string::npos) path.replace(pos, ph.size(), it->second); }
            return std::string("GET ") + path;
        }
        std::string postClipzyStore(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/api/store";
            return std::string("POST ") + path;
        }
    };
    ClipzyZaiXianJianTieBanApi clipzyZaiXianJianTieBan() { return ClipzyZaiXianJianTieBanApi(this); }
    struct ConvertApi {
        Client* c;
        ConvertApi(Client* cli): c(cli) {}
        std::string getConvertUnixtime(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/convert/unixtime";
            return std::string("GET ") + path;
        }
        std::string postConvertJson(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/convert/json";
            return std::string("POST ") + path;
        }
    };
    ConvertApi convert() { return ConvertApi(this); }
    struct DailyApi {
        Client* c;
        DailyApi(Client* cli): c(cli) {}
        std::string getDailyNewsImage(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/daily/news-image";
            return std::string("GET ") + path;
        }
    };
    DailyApi daily() { return DailyApi(this); }
    struct GameApi {
        Client* c;
        GameApi(Client* cli): c(cli) {}
        std::string getGameEpicFree(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/game/epic-free";
            return std::string("GET ") + path;
        }
        std::string getGameMinecraftHistoryid(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/game/minecraft/historyid";
            return std::string("GET ") + path;
        }
        std::string getGameMinecraftServerstatus(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/game/minecraft/serverstatus";
            return std::string("GET ") + path;
        }
        std::string getGameMinecraftUserinfo(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/game/minecraft/userinfo";
            return std::string("GET ") + path;
        }
        std::string getGameSteamSummary(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/game/steam/summary";
            return std::string("GET ") + path;
        }
    };
    GameApi game() { return GameApi(this); }
    struct ImageApi {
        Client* c;
        ImageApi(Client* cli): c(cli) {}
        std::string getAvatarGravatar(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/avatar/gravatar";
            return std::string("GET ") + path;
        }
        std::string getImageBingDaily(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/image/bing-daily";
            return std::string("GET ") + path;
        }
        std::string getImageMotou(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/image/motou";
            return std::string("GET ") + path;
        }
        std::string getImageQrcode(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/image/qrcode";
            return std::string("GET ") + path;
        }
        std::string getImageTobase64(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/image/tobase64";
            return std::string("GET ") + path;
        }
        std::string postImageCompress(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/image/compress";
            return std::string("POST ") + path;
        }
        std::string postImageFrombase64(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/image/frombase64";
            return std::string("POST ") + path;
        }
        std::string postImageMotou(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/image/motou";
            return std::string("POST ") + path;
        }
        std::string postImageSpeechless(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/image/speechless";
            return std::string("POST ") + path;
        }
        std::string postImageSvg(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/image/svg";
            return std::string("POST ") + path;
        }
    };
    ImageApi image() { return ImageApi(this); }
    struct MiscApi {
        Client* c;
        MiscApi(Client* cli): c(cli) {}
        std::string getHistoryProgrammer(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/history/programmer";
            return std::string("GET ") + path;
        }
        std::string getHistoryProgrammerToday(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/history/programmer/today";
            return std::string("GET ") + path;
        }
        std::string getMiscHotboard(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/misc/hotboard";
            return std::string("GET ") + path;
        }
        std::string getMiscPhoneinfo(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/misc/phoneinfo";
            return std::string("GET ") + path;
        }
        std::string getMiscRandomnumber(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/misc/randomnumber";
            return std::string("GET ") + path;
        }
        std::string getMiscTimestamp(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/misc/timestamp";
            return std::string("GET ") + path;
        }
        std::string getMiscTrackingCarriers(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/misc/tracking/carriers";
            return std::string("GET ") + path;
        }
        std::string getMiscTrackingDetect(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/misc/tracking/detect";
            return std::string("GET ") + path;
        }
        std::string getMiscTrackingQuery(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/misc/tracking/query";
            return std::string("GET ") + path;
        }
        std::string getMiscWeather(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/misc/weather";
            return std::string("GET ") + path;
        }
        std::string getMiscWorldtime(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/misc/worldtime";
            return std::string("GET ") + path;
        }
    };
    MiscApi misc() { return MiscApi(this); }
    struct NetworkApi {
        Client* c;
        NetworkApi(Client* cli): c(cli) {}
        std::string getNetworkDns(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/dns";
            return std::string("GET ") + path;
        }
        std::string getNetworkIcp(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/icp";
            return std::string("GET ") + path;
        }
        std::string getNetworkIpinfo(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/ipinfo";
            return std::string("GET ") + path;
        }
        std::string getNetworkMyip(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/myip";
            return std::string("GET ") + path;
        }
        std::string getNetworkPing(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/ping";
            return std::string("GET ") + path;
        }
        std::string getNetworkPingmyip(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/pingmyip";
            return std::string("GET ") + path;
        }
        std::string getNetworkPortscan(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/portscan";
            return std::string("GET ") + path;
        }
        std::string getNetworkUrlstatus(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/urlstatus";
            return std::string("GET ") + path;
        }
        std::string getNetworkWhois(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/whois";
            return std::string("GET ") + path;
        }
        std::string getNetworkWxdomain(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/network/wxdomain";
            return std::string("GET ") + path;
        }
    };
    NetworkApi network() { return NetworkApi(this); }
    struct PoemApi {
        Client* c;
        PoemApi(Client* cli): c(cli) {}
        std::string getSaying(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/saying";
            return std::string("GET ") + path;
        }
    };
    PoemApi poem() { return PoemApi(this); }
    struct RandomApi {
        Client* c;
        RandomApi(Client* cli): c(cli) {}
        std::string getAnswerbookAsk(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/answerbook/ask";
            return std::string("GET ") + path;
        }
        std::string getRandomImage(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/random/image";
            return std::string("GET ") + path;
        }
        std::string getRandomString(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/random/string";
            return std::string("GET ") + path;
        }
        std::string postAnswerbookAsk(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/answerbook/ask";
            return std::string("POST ") + path;
        }
    };
    RandomApi random() { return RandomApi(this); }
    struct SocialApi {
        Client* c;
        SocialApi(Client* cli): c(cli) {}
        std::string getGithubRepo(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/github/repo";
            return std::string("GET ") + path;
        }
        std::string getSocialBilibiliArchives(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/social/bilibili/archives";
            return std::string("GET ") + path;
        }
        std::string getSocialBilibiliLiveroom(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/social/bilibili/liveroom";
            return std::string("GET ") + path;
        }
        std::string getSocialBilibiliReplies(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/social/bilibili/replies";
            return std::string("GET ") + path;
        }
        std::string getSocialBilibiliUserinfo(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/social/bilibili/userinfo";
            return std::string("GET ") + path;
        }
        std::string getSocialBilibiliVideoinfo(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/social/bilibili/videoinfo";
            return std::string("GET ") + path;
        }
        std::string getSocialQqGroupinfo(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/social/qq/groupinfo";
            return std::string("GET ") + path;
        }
        std::string getSocialQqUserinfo(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/social/qq/userinfo";
            return std::string("GET ") + path;
        }
    };
    SocialApi social() { return SocialApi(this); }
    struct StatusApi {
        Client* c;
        StatusApi(Client* cli): c(cli) {}
        std::string getStatusRatelimit(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/status/ratelimit";
            return std::string("GET ") + path;
        }
        std::string getStatusUsage(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/status/usage";
            return std::string("GET ") + path;
        }
    };
    StatusApi status() { return StatusApi(this); }
    struct TextApi {
        Client* c;
        TextApi(Client* cli): c(cli) {}
        std::string getTextMd5(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/text/md5";
            return std::string("GET ") + path;
        }
        std::string postTextAesDecrypt(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/text/aes/decrypt";
            return std::string("POST ") + path;
        }
        std::string postTextAesEncrypt(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/text/aes/encrypt";
            return std::string("POST ") + path;
        }
        std::string postTextAnalyze(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/text/analyze";
            return std::string("POST ") + path;
        }
        std::string postTextBase64Decode(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/text/base64/decode";
            return std::string("POST ") + path;
        }
        std::string postTextBase64Encode(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/text/base64/encode";
            return std::string("POST ") + path;
        }
        std::string postTextMd5(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/text/md5";
            return std::string("POST ") + path;
        }
        std::string postTextMd5Verify(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/text/md5/verify";
            return std::string("POST ") + path;
        }
    };
    TextApi text() { return TextApi(this); }
    struct TranslateApi {
        Client* c;
        TranslateApi(Client* cli): c(cli) {}
        std::string getAiTranslateLanguages(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/ai/translate/languages";
            return std::string("GET ") + path;
        }
        std::string postAiTranslate(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/ai/translate";
            return std::string("POST ") + path;
        }
        std::string postTranslateText(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/translate/text";
            return std::string("POST ") + path;
        }
    };
    TranslateApi translate() { return TranslateApi(this); }
    struct WebparseApi {
        Client* c;
        WebparseApi(Client* cli): c(cli) {}
        std::string getWebTomarkdownAsyncStatus(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/web/tomarkdown/async/{task_id}";
            if (auto it = args.find("task_id"); it != args.end()) { auto ph = std::string("{") + "task_id" + "}"; auto pos = path.find(ph); if (pos!=std::string::npos) path.replace(pos, ph.size(), it->second); }
            return std::string("GET ") + path;
        }
        std::string getWebparseExtractimages(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/webparse/extractimages";
            return std::string("GET ") + path;
        }
        std::string getWebparseMetadata(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/webparse/metadata";
            return std::string("GET ") + path;
        }
        std::string postWebTomarkdownAsync(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/web/tomarkdown/async";
            return std::string("POST ") + path;
        }
    };
    WebparseApi webparse() { return WebparseApi(this); }
    struct MinGanCiShiBieApi {
        Client* c;
        MinGanCiShiBieApi(Client* cli): c(cli) {}
        std::string getSensitiveWordAnalyzeQuery(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/sensitive-word/analyze-query";
            return std::string("GET ") + path;
        }
        std::string postSensitiveWordAnalyze(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/sensitive-word/analyze";
            return std::string("POST ") + path;
        }
        std::string postSensitiveWordQuickCheck(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/text/profanitycheck";
            return std::string("POST ") + path;
        }
    };
    MinGanCiShiBieApi minGanCiShiBie() { return MinGanCiShiBieApi(this); }
    struct ZhiNengSouSuoApi {
        Client* c;
        ZhiNengSouSuoApi(Client* cli): c(cli) {}
        std::string getSearchEngines(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/search/engines";
            return std::string("GET ") + path;
        }
        std::string postSearchAggregate(const std::map<std::string, std::string>& args = {}) {
            // TODO: integrate with internal client or curl
            std::string path = "/search/aggregate";
            return std::string("POST ") + path;
        }
    };
    ZhiNengSouSuoApi zhiNengSouSuo() { return ZhiNengSouSuoApi(this); }
};

} // namespace
