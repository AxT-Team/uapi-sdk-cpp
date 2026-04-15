#pragma once
#include <string>
#include <stdexcept>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <chrono>
#include <optional>

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
    std::string payload;
    struct ResponseMeta {
        std::string requestId;
        long long retryAfterSeconds = -1;
        std::string debitStatus;
        long long creditsRequested = -1;
        long long creditsCharged = -1;
        std::string creditsPricing;
        long long activeQuotaBuckets = -1;
        bool stopOnEmpty = false;
        bool hasStopOnEmpty = false;
        std::string rateLimitPolicyRaw;
        std::string rateLimitRaw;
        long long balanceLimitCents = -1;
        long long balanceRemainingCents = -1;
        long long quotaLimitCredits = -1;
        long long quotaRemainingCredits = -1;
        long long visitorQuotaLimitCredits = -1;
        long long visitorQuotaRemainingCredits = -1;
        std::map<std::string, std::string> rawHeaders;
    } meta;
    UapiError(std::string c, int s, std::string msg, std::string raw = ""): UapiError(std::move(c), s, std::move(msg), std::move(raw), ResponseMeta{}) {}
    UapiError(std::string c, int s, std::string msg, std::string raw, ResponseMeta responseMeta): std::runtime_error("["+std::to_string(s)+"] "+c+": "+msg), code(std::move(c)), status(s), payload(std::move(raw)), meta(std::move(responseMeta)) {}
};
struct ApiErrorError: public UapiError { using UapiError::UapiError; };
struct AvatarNotFoundError: public UapiError { using UapiError::UapiError; };
struct ConversionFailedError: public UapiError { using UapiError::UapiError; };
struct FileOpenErrorError: public UapiError { using UapiError::UapiError; };
struct FileRequiredError: public UapiError { using UapiError::UapiError; };
struct InsufficientCreditsError: public UapiError { using UapiError::UapiError; };
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
struct VisitorMonthlyQuotaExhaustedError: public UapiError { using UapiError::UapiError; };

class Client {
public:
    Client(std::string baseUrl = "https://uapis.cn", std::string tok = "", bool disableCache = false);
    const UapiError::ResponseMeta& lastResponseMeta() const { return lastMeta; }
    struct ClipzyZaiXianJianTieBanApi {
        Client* c;
        explicit ClipzyZaiXianJianTieBanApi(Client* cli): c(cli) {}
        std::string getClipzyGet(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/api/get";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("id"); it != args.end()) query["id"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getClipzyRaw(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/api/raw/{id}";
            if (auto it = args.find("id"); it != args.end()) { auto ph = std::string("{") + "id" + "}"; auto pos = path.find(ph); if (pos!=std::string::npos) path.replace(pos, ph.size(), it->second); }
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("key"); it != args.end()) query["key"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postClipzyStore(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/api/store";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("compressedData"); it != args.end()) body["compressedData"] = it->second;
            if (auto it = args.find("ttl"); it != args.end()) body["ttl"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
    };
    ClipzyZaiXianJianTieBanApi clipzyZaiXianJianTieBan() { return ClipzyZaiXianJianTieBanApi(this); }
    struct ConvertApi {
        Client* c;
        explicit ConvertApi(Client* cli): c(cli) {}
        std::string getConvertUnixtime(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/convert/unixtime";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("time"); it != args.end()) query["time"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postConvertJson(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/convert/json";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("content"); it != args.end()) body["content"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
    };
    ConvertApi convert() { return ConvertApi(this); }
    struct DailyApi {
        Client* c;
        explicit DailyApi(Client* cli): c(cli) {}
        std::string getDailyNewsImage(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/daily/news-image";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
    };
    DailyApi daily() { return DailyApi(this); }
    struct GameApi {
        Client* c;
        explicit GameApi(Client* cli): c(cli) {}
        std::string getGameEpicFree(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/epic-free";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getGameMinecraftHistoryid(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/minecraft/historyid";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("name"); it != args.end()) query["name"] = it->second;
            if (auto it = args.find("uuid"); it != args.end()) query["uuid"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getGameMinecraftServerstatus(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/minecraft/serverstatus";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("server"); it != args.end()) query["server"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getGameMinecraftUserinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/minecraft/userinfo";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("username"); it != args.end()) query["username"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getGameSteamSummary(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/game/steam/summary";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("steamid"); it != args.end()) query["steamid"] = it->second;
            if (auto it = args.find("id"); it != args.end()) query["id"] = it->second;
            if (auto it = args.find("id3"); it != args.end()) query["id3"] = it->second;
            if (auto it = args.find("key"); it != args.end()) query["key"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
    };
    GameApi game() { return GameApi(this); }
    struct ImageApi {
        Client* c;
        explicit ImageApi(Client* cli): c(cli) {}
        std::string getAvatarGravatar(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/avatar/gravatar";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("email"); it != args.end()) query["email"] = it->second;
            if (auto it = args.find("hash"); it != args.end()) query["hash"] = it->second;
            if (auto it = args.find("s"); it != args.end()) query["s"] = it->second;
            if (auto it = args.find("d"); it != args.end()) query["d"] = it->second;
            if (auto it = args.find("r"); it != args.end()) query["r"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getImageBingDaily(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/bing-daily";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("date"); it != args.end()) query["date"] = it->second;
            if (auto it = args.find("resolution"); it != args.end()) query["resolution"] = it->second;
            if (auto it = args.find("format"); it != args.end()) query["format"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getImageBingDailyHistory(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/bing-daily/history";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("date"); it != args.end()) query["date"] = it->second;
            if (auto it = args.find("resolution"); it != args.end()) query["resolution"] = it->second;
            if (auto it = args.find("page"); it != args.end()) query["page"] = it->second;
            if (auto it = args.find("page_size"); it != args.end()) query["page_size"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getImageMotou(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/motou";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("qq"); it != args.end()) query["qq"] = it->second;
            if (auto it = args.find("bg_color"); it != args.end()) query["bg_color"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getImageQrcode(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/qrcode";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("text"); it != args.end()) query["text"] = it->second;
            if (auto it = args.find("size"); it != args.end()) query["size"] = it->second;
            if (auto it = args.find("format"); it != args.end()) query["format"] = it->second;
            if (auto it = args.find("transparent"); it != args.end()) query["transparent"] = it->second;
            if (auto it = args.find("fgcolor"); it != args.end()) query["fgcolor"] = it->second;
            if (auto it = args.find("bgcolor"); it != args.end()) query["bgcolor"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getImageTobase64(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/tobase64";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("url"); it != args.end()) query["url"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postImageCompress(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/compress";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("level"); it != args.end()) query["level"] = it->second;
            if (auto it = args.find("format"); it != args.end()) query["format"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("file"); it != args.end()) body["file"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postImageDecode(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/decode";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("width"); it != args.end()) query["width"] = it->second;
            if (auto it = args.find("height"); it != args.end()) query["height"] = it->second;
            if (auto it = args.find("max_width"); it != args.end()) query["max_width"] = it->second;
            if (auto it = args.find("max_height"); it != args.end()) query["max_height"] = it->second;
            if (auto it = args.find("format"); it != args.end()) query["format"] = it->second;
            if (auto it = args.find("color_mode"); it != args.end()) query["color_mode"] = it->second;
            if (auto it = args.find("fit"); it != args.end()) query["fit"] = it->second;
            if (auto it = args.find("background"); it != args.end()) query["background"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("file"); it != args.end()) body["file"] = it->second;
            if (auto it = args.find("url"); it != args.end()) body["url"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postImageFrombase64(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/frombase64";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("imageData"); it != args.end()) body["imageData"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postImageMotou(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/motou";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("bg_color"); it != args.end()) body["bg_color"] = it->second;
            if (auto it = args.find("file"); it != args.end()) body["file"] = it->second;
            if (auto it = args.find("image_url"); it != args.end()) body["image_url"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postImageNsfw(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/nsfw";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("file"); it != args.end()) body["file"] = it->second;
            if (auto it = args.find("url"); it != args.end()) body["url"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postImageOcr(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/ocr";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("enable_cls"); it != args.end()) body["enable_cls"] = it->second;
            if (auto it = args.find("file"); it != args.end()) body["file"] = it->second;
            if (auto it = args.find("image_base64"); it != args.end()) body["image_base64"] = it->second;
            if (auto it = args.find("image_name"); it != args.end()) body["image_name"] = it->second;
            if (auto it = args.find("need_location"); it != args.end()) body["need_location"] = it->second;
            if (auto it = args.find("return_markdown"); it != args.end()) body["return_markdown"] = it->second;
            if (auto it = args.find("url"); it != args.end()) body["url"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postImageSpeechless(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/speechless";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("bottom_text"); it != args.end()) body["bottom_text"] = it->second;
            if (auto it = args.find("top_text"); it != args.end()) body["top_text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postImageSvg(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/image/svg";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("format"); it != args.end()) query["format"] = it->second;
            if (auto it = args.find("width"); it != args.end()) query["width"] = it->second;
            if (auto it = args.find("height"); it != args.end()) query["height"] = it->second;
            if (auto it = args.find("quality"); it != args.end()) query["quality"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("file"); it != args.end()) body["file"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
    };
    ImageApi image() { return ImageApi(this); }
    struct MiscApi {
        Client* c;
        explicit MiscApi(Client* cli): c(cli) {}
        std::string getHistoryProgrammer(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/history/programmer";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("month"); it != args.end()) query["month"] = it->second;
            if (auto it = args.find("day"); it != args.end()) query["day"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getHistoryProgrammerToday(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/history/programmer/today";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscDistrict(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/district";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("keywords"); it != args.end()) query["keywords"] = it->second;
            if (auto it = args.find("adcode"); it != args.end()) query["adcode"] = it->second;
            if (auto it = args.find("lat"); it != args.end()) query["lat"] = it->second;
            if (auto it = args.find("lng"); it != args.end()) query["lng"] = it->second;
            if (auto it = args.find("level"); it != args.end()) query["level"] = it->second;
            if (auto it = args.find("country"); it != args.end()) query["country"] = it->second;
            if (auto it = args.find("limit"); it != args.end()) query["limit"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscHolidayCalendar(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/holiday-calendar";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("date"); it != args.end()) query["date"] = it->second;
            if (auto it = args.find("month"); it != args.end()) query["month"] = it->second;
            if (auto it = args.find("year"); it != args.end()) query["year"] = it->second;
            if (auto it = args.find("timezone"); it != args.end()) query["timezone"] = it->second;
            if (auto it = args.find("holiday_type"); it != args.end()) query["holiday_type"] = it->second;
            if (auto it = args.find("include_nearby"); it != args.end()) query["include_nearby"] = it->second;
            if (auto it = args.find("nearby_limit"); it != args.end()) query["nearby_limit"] = it->second;
            if (auto it = args.find("exclude_past"); it != args.end()) query["exclude_past"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscHotboard(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/hotboard";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("type"); it != args.end()) query["type"] = it->second;
            if (auto it = args.find("time"); it != args.end()) query["time"] = it->second;
            if (auto it = args.find("keyword"); it != args.end()) query["keyword"] = it->second;
            if (auto it = args.find("time_start"); it != args.end()) query["time_start"] = it->second;
            if (auto it = args.find("time_end"); it != args.end()) query["time_end"] = it->second;
            if (auto it = args.find("limit"); it != args.end()) query["limit"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscLunartime(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/lunartime";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("ts"); it != args.end()) query["ts"] = it->second;
            if (auto it = args.find("timezone"); it != args.end()) query["timezone"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscPhoneinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/phoneinfo";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("phone"); it != args.end()) query["phone"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscRandomnumber(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/randomnumber";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("min"); it != args.end()) query["min"] = it->second;
            if (auto it = args.find("max"); it != args.end()) query["max"] = it->second;
            if (auto it = args.find("count"); it != args.end()) query["count"] = it->second;
            if (auto it = args.find("allow_repeat"); it != args.end()) query["allow_repeat"] = it->second;
            if (auto it = args.find("allow_decimal"); it != args.end()) query["allow_decimal"] = it->second;
            if (auto it = args.find("decimal_places"); it != args.end()) query["decimal_places"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscTimestamp(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/timestamp";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("ts"); it != args.end()) query["ts"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscTrackingCarriers(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/tracking/carriers";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscTrackingDetect(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/tracking/detect";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("tracking_number"); it != args.end()) query["tracking_number"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscTrackingQuery(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/tracking/query";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("tracking_number"); it != args.end()) query["tracking_number"] = it->second;
            if (auto it = args.find("carrier_code"); it != args.end()) query["carrier_code"] = it->second;
            if (auto it = args.find("phone"); it != args.end()) query["phone"] = it->second;
            if (auto it = args.find("full"); it != args.end()) query["full"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscWeather(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/weather";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("city"); it != args.end()) query["city"] = it->second;
            if (auto it = args.find("adcode"); it != args.end()) query["adcode"] = it->second;
            if (auto it = args.find("extended"); it != args.end()) query["extended"] = it->second;
            if (auto it = args.find("forecast"); it != args.end()) query["forecast"] = it->second;
            if (auto it = args.find("hourly"); it != args.end()) query["hourly"] = it->second;
            if (auto it = args.find("minutely"); it != args.end()) query["minutely"] = it->second;
            if (auto it = args.find("indices"); it != args.end()) query["indices"] = it->second;
            if (auto it = args.find("lang"); it != args.end()) query["lang"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getMiscWorldtime(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/worldtime";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("city"); it != args.end()) query["city"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postMiscDateDiff(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/misc/date-diff";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("end_date"); it != args.end()) body["end_date"] = it->second;
            if (auto it = args.find("format"); it != args.end()) body["format"] = it->second;
            if (auto it = args.find("start_date"); it != args.end()) body["start_date"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
    };
    MiscApi misc() { return MiscApi(this); }
    struct NetworkApi {
        Client* c;
        explicit NetworkApi(Client* cli): c(cli) {}
        std::string getNetworkDns(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/dns";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("domain"); it != args.end()) query["domain"] = it->second;
            if (auto it = args.find("type"); it != args.end()) query["type"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getNetworkIcp(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/icp";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("domain"); it != args.end()) query["domain"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getNetworkIpinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/ipinfo";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("ip"); it != args.end()) query["ip"] = it->second;
            if (auto it = args.find("source"); it != args.end()) query["source"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getNetworkMyip(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/myip";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("source"); it != args.end()) query["source"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getNetworkPing(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/ping";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("host"); it != args.end()) query["host"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getNetworkPingmyip(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/pingmyip";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getNetworkPortscan(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/portscan";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("host"); it != args.end()) query["host"] = it->second;
            if (auto it = args.find("port"); it != args.end()) query["port"] = it->second;
            if (auto it = args.find("protocol"); it != args.end()) query["protocol"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getNetworkUrlstatus(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/urlstatus";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("url"); it != args.end()) query["url"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getNetworkWhois(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/whois";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("domain"); it != args.end()) query["domain"] = it->second;
            if (auto it = args.find("format"); it != args.end()) query["format"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getNetworkWxdomain(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/network/wxdomain";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("domain"); it != args.end()) query["domain"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
    };
    NetworkApi network() { return NetworkApi(this); }
    struct PoemApi {
        Client* c;
        explicit PoemApi(Client* cli): c(cli) {}
        std::string getSaying(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/saying";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
    };
    PoemApi poem() { return PoemApi(this); }
    struct RandomApi {
        Client* c;
        explicit RandomApi(Client* cli): c(cli) {}
        std::string getAnswerbookAsk(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/answerbook/ask";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("question"); it != args.end()) query["question"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getRandomImage(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/random/image";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("category"); it != args.end()) query["category"] = it->second;
            if (auto it = args.find("type"); it != args.end()) query["type"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getRandomString(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/random/string";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("length"); it != args.end()) query["length"] = it->second;
            if (auto it = args.find("type"); it != args.end()) query["type"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postAnswerbookAsk(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/answerbook/ask";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("question"); it != args.end()) body["question"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
    };
    RandomApi random() { return RandomApi(this); }
    struct SocialApi {
        Client* c;
        explicit SocialApi(Client* cli): c(cli) {}
        std::string getGithubRepo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/github/repo";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("repo"); it != args.end()) query["repo"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getGithubUser(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/github/user";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("user"); it != args.end()) query["user"] = it->second;
            if (auto it = args.find("activity"); it != args.end()) query["activity"] = it->second;
            if (auto it = args.find("activity_scope"); it != args.end()) query["activity_scope"] = it->second;
            if (auto it = args.find("org"); it != args.end()) query["org"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getSocialBilibiliArchives(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/archives";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("mid"); it != args.end()) query["mid"] = it->second;
            if (auto it = args.find("keywords"); it != args.end()) query["keywords"] = it->second;
            if (auto it = args.find("orderby"); it != args.end()) query["orderby"] = it->second;
            if (auto it = args.find("ps"); it != args.end()) query["ps"] = it->second;
            if (auto it = args.find("pn"); it != args.end()) query["pn"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getSocialBilibiliLiveroom(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/liveroom";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("mid"); it != args.end()) query["mid"] = it->second;
            if (auto it = args.find("room_id"); it != args.end()) query["room_id"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getSocialBilibiliReplies(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/replies";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("oid"); it != args.end()) query["oid"] = it->second;
            if (auto it = args.find("sort"); it != args.end()) query["sort"] = it->second;
            if (auto it = args.find("ps"); it != args.end()) query["ps"] = it->second;
            if (auto it = args.find("pn"); it != args.end()) query["pn"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getSocialBilibiliUserinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/userinfo";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("uid"); it != args.end()) query["uid"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getSocialBilibiliVideoinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/bilibili/videoinfo";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("aid"); it != args.end()) query["aid"] = it->second;
            if (auto it = args.find("bvid"); it != args.end()) query["bvid"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getSocialQqGroupinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/qq/groupinfo";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("group_id"); it != args.end()) query["group_id"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getSocialQqUserinfo(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/social/qq/userinfo";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("qq"); it != args.end()) query["qq"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
    };
    SocialApi social() { return SocialApi(this); }
    struct StatusApi {
        Client* c;
        explicit StatusApi(Client* cli): c(cli) {}
        std::string getStatusRatelimit(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/status/ratelimit";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getStatusUsage(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/status/usage";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("path"); it != args.end()) query["path"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
    };
    StatusApi status() { return StatusApi(this); }
    struct TextApi {
        Client* c;
        explicit TextApi(Client* cli): c(cli) {}
        std::string getTextMd5(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/md5";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("text"); it != args.end()) query["text"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postTextAesDecrypt(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/aes/decrypt";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("key"); it != args.end()) body["key"] = it->second;
            if (auto it = args.find("nonce"); it != args.end()) body["nonce"] = it->second;
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextAesDecryptAdvanced(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/aes/decrypt-advanced";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("iv"); it != args.end()) body["iv"] = it->second;
            if (auto it = args.find("key"); it != args.end()) body["key"] = it->second;
            if (auto it = args.find("mode"); it != args.end()) body["mode"] = it->second;
            if (auto it = args.find("padding"); it != args.end()) body["padding"] = it->second;
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextAesEncrypt(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/aes/encrypt";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("key"); it != args.end()) body["key"] = it->second;
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextAesEncryptAdvanced(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/aes/encrypt-advanced";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("iv"); it != args.end()) body["iv"] = it->second;
            if (auto it = args.find("key"); it != args.end()) body["key"] = it->second;
            if (auto it = args.find("mode"); it != args.end()) body["mode"] = it->second;
            if (auto it = args.find("output_format"); it != args.end()) body["output_format"] = it->second;
            if (auto it = args.find("padding"); it != args.end()) body["padding"] = it->second;
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextAnalyze(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/analyze";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextBase64Decode(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/base64/decode";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextBase64Encode(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/base64/encode";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextConvert(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/convert";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("from"); it != args.end()) body["from"] = it->second;
            if (auto it = args.find("options"); it != args.end()) body["options"] = it->second;
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            if (auto it = args.find("to"); it != args.end()) body["to"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextMarkdownToHtml(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/markdown-to-html";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("format"); it != args.end()) body["format"] = it->second;
            if (auto it = args.find("sanitize"); it != args.end()) body["sanitize"] = it->second;
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextMarkdownToPdf(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/markdown-to-pdf";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("paper_size"); it != args.end()) body["paper_size"] = it->second;
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            if (auto it = args.find("theme"); it != args.end()) body["theme"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextMd5(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/md5";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTextMd5Verify(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/md5/verify";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("hash"); it != args.end()) body["hash"] = it->second;
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
    };
    TextApi text() { return TextApi(this); }
    struct TranslateApi {
        Client* c;
        explicit TranslateApi(Client* cli): c(cli) {}
        std::string getAiTranslateLanguages(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/ai/translate/languages";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postAiTranslate(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/ai/translate";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("target_lang"); it != args.end()) query["target_lang"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("context"); it != args.end()) body["context"] = it->second;
            if (auto it = args.find("preserve_format"); it != args.end()) body["preserve_format"] = it->second;
            if (auto it = args.find("source_lang"); it != args.end()) body["source_lang"] = it->second;
            if (auto it = args.find("style"); it != args.end()) body["style"] = it->second;
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTranslateStream(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/translate/stream";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("from_lang"); it != args.end()) body["from_lang"] = it->second;
            if (auto it = args.find("query"); it != args.end()) body["query"] = it->second;
            if (auto it = args.find("to_lang"); it != args.end()) body["to_lang"] = it->second;
            if (auto it = args.find("tone"); it != args.end()) body["tone"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postTranslateText(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/translate/text";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("to_lang"); it != args.end()) query["to_lang"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
    };
    TranslateApi translate() { return TranslateApi(this); }
    struct WebparseApi {
        Client* c;
        explicit WebparseApi(Client* cli): c(cli) {}
        std::string getWebTomarkdownAsyncStatus(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/web/tomarkdown/async/{task_id}";
            if (auto it = args.find("task_id"); it != args.end()) { auto ph = std::string("{") + "task_id" + "}"; auto pos = path.find(ph); if (pos!=std::string::npos) path.replace(pos, ph.size(), it->second); }
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getWebparseExtractimages(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/webparse/extractimages";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("url"); it != args.end()) query["url"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string getWebparseMetadata(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/webparse/metadata";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("url"); it != args.end()) query["url"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postWebTomarkdownAsync(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/web/tomarkdown/async";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("url"); it != args.end()) query["url"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("POST", path, query, body, disableCache);
        }
    };
    WebparseApi webparse() { return WebparseApi(this); }
    struct MinGanCiShiBieApi {
        Client* c;
        explicit MinGanCiShiBieApi(Client* cli): c(cli) {}
        std::string getSensitiveWordAnalyzeQuery(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/sensitive-word/analyze-query";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("keyword"); it != args.end()) query["keyword"] = it->second;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postSensitiveWordAnalyze(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/sensitive-word/analyze";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("keywords"); it != args.end()) body["keywords"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
        std::string postSensitiveWordQuickCheck(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/text/profanitycheck";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("text"); it != args.end()) body["text"] = it->second;
            return c->request("POST", path, query, body, disableCache);
        }
    };
    MinGanCiShiBieApi minGanCiShiBie() { return MinGanCiShiBieApi(this); }
    struct ZhiNengSouSuoApi {
        Client* c;
        explicit ZhiNengSouSuoApi(Client* cli): c(cli) {}
        std::string getSearchEngines(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/search/engines";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            return c->request("GET", path, query, body, disableCache);
        }
        std::string postSearchAggregate(const std::map<std::string, std::string>& args = {}) {
            std::string path = "/api/v1/search/aggregate";
            std::map<std::string, std::string> query;
            std::map<std::string, std::string> body;
            std::optional<bool> disableCache;
            if (auto it = args.find("_t"); it != args.end()) query["_t"] = it->second;
            if (auto it = args.find("disableCache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            if (!disableCache.has_value()) {
                if (auto it = args.find("disable_cache"); it != args.end()) disableCache = Client::parseOptionalBool(it->second);
            }
            if (auto it = args.find("fetch_full"); it != args.end()) body["fetch_full"] = it->second;
            if (auto it = args.find("filetype"); it != args.end()) body["filetype"] = it->second;
            if (auto it = args.find("query"); it != args.end()) body["query"] = it->second;
            if (auto it = args.find("site"); it != args.end()) body["site"] = it->second;
            if (auto it = args.find("sort"); it != args.end()) body["sort"] = it->second;
            if (auto it = args.find("time_range"); it != args.end()) body["time_range"] = it->second;
            return c->request("POST", path, query, body, disableCache);
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
    bool disableCacheDefault;
    mutable UapiError::ResponseMeta lastMeta;

    std::string request(const std::string& method, std::string path, const std::map<std::string, std::string>& query, const std::map<std::string, std::string>& body = {}, std::optional<bool> disableCache = std::nullopt) const;
    std::string buildQuery(const std::map<std::string, std::string>& query) const;
    std::map<std::string, std::string> applyCacheControl(const std::string& method, const std::map<std::string, std::string>& query, std::optional<bool> disableCache) const;
    static std::string urlEncode(const std::string& value);
    std::string defaultCode(int status) const;
    void raiseError(int status, const std::string& body) const;
    static std::string extractField(const std::string& body, const std::string& key);
    void setMetaFromHeaders(const std::map<std::string, std::string>& headers) const;
    static std::string headerValue(const std::map<std::string, std::string>& headers, const std::string& key);
    static long long parseLong(const std::string& value);
    static std::optional<bool> parseOptionalBool(const std::string& value);
    static std::string structuredValue(const std::string& raw, const std::string& name, const std::string& key);
    static std::string unquote(const std::string& value);
#ifdef _WIN32
    std::string sendWinHttp(const std::string& method, const std::string& pathAndQuery, const std::string& body = "") const;
    static std::wstring widen(const std::string& input);
    static std::string narrow(const std::wstring& input);
    static std::string queryHeaderValue(HINTERNET hRequest, const wchar_t* headerName);
#else
    std::string sendCurl(const std::string& method, const std::string& absoluteUrl, const std::string& body = "") const;
    static std::string shellEscape(const std::string& value);
#endif
};

inline Client::Client(std::string baseUrl, std::string tok, bool disableCache): host(), basePath("/"), port(443), secure(true), token(std::move(tok)), disableCacheDefault(disableCache) {
    if (baseUrl.empty()) baseUrl = "https://uapis.cn";
    auto schemePos = baseUrl.find("://");
    std::string scheme = schemePos == std::string::npos ? "https" : baseUrl.substr(0, schemePos);
    secure = (scheme == "https");
    std::string rest = schemePos == std::string::npos ? baseUrl : baseUrl.substr(schemePos + 3);
    auto slashPos = rest.find('/');
    host = slashPos == std::string::npos ? rest : rest.substr(0, slashPos);
    basePath = slashPos == std::string::npos ? "/" : rest.substr(slashPos);
    while (basePath.size() > 1 && basePath.back() == '/') basePath.pop_back();
    const std::string apiPrefix = "/api/v1";
    if (basePath.size() >= apiPrefix.size() && basePath.compare(basePath.size() - apiPrefix.size(), apiPrefix.size(), apiPrefix) == 0) {
        basePath.erase(basePath.size() - apiPrefix.size());
    }
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

inline std::string Client::request(const std::string& method, std::string path, const std::map<std::string, std::string>& query, const std::map<std::string, std::string>& body, std::optional<bool> disableCache) const {
    if (!path.empty() && path.front() == '/') path.erase(0, 1);
    std::string normalized = basePath;
    if (!normalized.empty() && normalized.back() == '/' && !path.empty()) {
        normalized += path;
    } else if (!path.empty()) {
        if (!normalized.empty() && normalized.back() != '/') normalized.push_back('/');
        normalized += path;
    }
    if (normalized.empty()) normalized = "/";
    auto queryString = buildQuery(applyCacheControl(method, query, disableCache));
    std::string jsonBody;
    if (!body.empty()) {
        jsonBody = "{";
        bool first = true;
        for (const auto& kv : body) {
            if (!first) jsonBody += ",";
            first = false;
            jsonBody += "\"" + kv.first + "\":\"" + kv.second + "\"";
        }
        jsonBody += "}";
    }
#ifdef _WIN32
    return sendWinHttp(method, normalized + queryString, jsonBody);
#else
    return sendCurl(method, origin + normalized + queryString, jsonBody);
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

inline std::map<std::string, std::string> Client::applyCacheControl(const std::string& method, const std::map<std::string, std::string>& query, std::optional<bool> disableCache) const {
    if (method != "GET") return query;
    if (query.find("_t") != query.end()) return query;
    bool effectiveDisableCache = disableCache.has_value() ? *disableCache : disableCacheDefault;
    if (!effectiveDisableCache) return query;
    auto next = query;
    const auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    next["_t"] = std::to_string(now);
    return next;
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
    if (status == 402) return "INSUFFICIENT_CREDITS";
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
    if (code.empty()) code = extractField(body, "error");
    if (code.empty()) code = defaultCode(status);
    std::string message = extractField(body, "message");
    if (message.empty()) message = "HTTP " + std::to_string(status);
    if (false) {}
    else if (code == "API_ERROR") throw ApiErrorError(code, status, message, body, lastMeta);
    else if (code == "AVATAR_NOT_FOUND") throw AvatarNotFoundError(code, status, message, body, lastMeta);
    else if (code == "CONVERSION_FAILED") throw ConversionFailedError(code, status, message, body, lastMeta);
    else if (code == "FILE_OPEN_ERROR") throw FileOpenErrorError(code, status, message, body, lastMeta);
    else if (code == "FILE_REQUIRED") throw FileRequiredError(code, status, message, body, lastMeta);
    else if (code == "INSUFFICIENT_CREDITS") throw InsufficientCreditsError(code, status, message, body, lastMeta);
    else if (code == "INTERNAL_SERVER_ERROR") throw InternalServerErrorError(code, status, message, body, lastMeta);
    else if (code == "INVALID_PARAMETER") throw InvalidParameterError(code, status, message, body, lastMeta);
    else if (code == "INVALID_PARAMS") throw InvalidParamsError(code, status, message, body, lastMeta);
    else if (code == "NOT_FOUND") throw NotFoundError(code, status, message, body, lastMeta);
    else if (code == "NO_MATCH") throw NoMatchError(code, status, message, body, lastMeta);
    else if (code == "NO_TRACKING_DATA") throw NoTrackingDataError(code, status, message, body, lastMeta);
    else if (code == "PHONE_INFO_FAILED") throw PhoneInfoFailedError(code, status, message, body, lastMeta);
    else if (code == "RECOGNITION_FAILED") throw RecognitionFailedError(code, status, message, body, lastMeta);
    else if (code == "REQUEST_ENTITY_TOO_LARGE") throw RequestEntityTooLargeError(code, status, message, body, lastMeta);
    else if (code == "SERVICE_BUSY") throw ServiceBusyError(code, status, message, body, lastMeta);
    else if (code == "TIMEZONE_NOT_FOUND") throw TimezoneNotFoundError(code, status, message, body, lastMeta);
    else if (code == "UNAUTHORIZED") throw UnauthorizedError(code, status, message, body, lastMeta);
    else if (code == "UNSUPPORTED_CARRIER") throw UnsupportedCarrierError(code, status, message, body, lastMeta);
    else if (code == "UNSUPPORTED_FORMAT") throw UnsupportedFormatError(code, status, message, body, lastMeta);
    else if (code == "VISITOR_MONTHLY_QUOTA_EXHAUSTED") throw VisitorMonthlyQuotaExhaustedError(code, status, message, body, lastMeta);
    else throw UapiError(code, status, message, body, lastMeta);
}

inline std::string Client::headerValue(const std::map<std::string, std::string>& headers, const std::string& key) {
    auto it = headers.find(key);
    return it == headers.end() ? std::string() : it->second;
}

inline long long Client::parseLong(const std::string& value) {
    if (value.empty()) return -1;
    try {
        return std::stoll(value);
    } catch (...) {
        return -1;
    }
}

inline std::optional<bool> Client::parseOptionalBool(const std::string& value) {
    auto normalized = value;
    normalized.erase(normalized.begin(), std::find_if(normalized.begin(), normalized.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    normalized.erase(std::find_if(normalized.rbegin(), normalized.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), normalized.end());
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    if (normalized == "1" || normalized == "true" || normalized == "yes" || normalized == "on") return true;
    if (normalized == "0" || normalized == "false" || normalized == "no" || normalized == "off") return false;
    return std::nullopt;
}

inline std::string Client::unquote(const std::string& value) {
    auto start = value.find_first_not_of(" \t\r\n");
    auto end = value.find_last_not_of(" \t\r\n");
    if (start == std::string::npos || end == std::string::npos) return {};
    auto trimmed = value.substr(start, end - start + 1);
    if (trimmed.size() >= 2 && trimmed.front() == '"' && trimmed.back() == '"') {
        return trimmed.substr(1, trimmed.size() - 2);
    }
    return trimmed;
}

inline std::string Client::structuredValue(const std::string& raw, const std::string& name, const std::string& key) {
    std::stringstream ss(raw);
    std::string item;
    while (std::getline(ss, item, ',')) {
        std::stringstream itemStream(item);
        std::string segment;
        if (!std::getline(itemStream, segment, ';')) continue;
        segment = unquote(segment);
        if (segment != name) continue;
        while (std::getline(itemStream, segment, ';')) {
            auto eq = segment.find('=');
            if (eq == std::string::npos) continue;
            auto k = segment.substr(0, eq);
            auto v = unquote(segment.substr(eq + 1));
            while (!k.empty() && std::isspace(static_cast<unsigned char>(k.front()))) k.erase(k.begin());
            while (!k.empty() && std::isspace(static_cast<unsigned char>(k.back()))) k.pop_back();
            if (k == key) return v;
        }
    }
    return {};
}

inline void Client::setMetaFromHeaders(const std::map<std::string, std::string>& headers) const {
    lastMeta = UapiError::ResponseMeta{};
    lastMeta.rawHeaders = headers;
    lastMeta.requestId = headerValue(headers, "x-request-id");
    lastMeta.retryAfterSeconds = parseLong(headerValue(headers, "retry-after"));
    lastMeta.debitStatus = headerValue(headers, "uapi-debit-status");
    lastMeta.creditsRequested = parseLong(headerValue(headers, "uapi-credits-requested"));
    lastMeta.creditsCharged = parseLong(headerValue(headers, "uapi-credits-charged"));
    lastMeta.creditsPricing = headerValue(headers, "uapi-credits-pricing");
    lastMeta.activeQuotaBuckets = parseLong(headerValue(headers, "uapi-quota-active-buckets"));
    auto stopOnEmpty = headerValue(headers, "uapi-stop-on-empty");
    if (!stopOnEmpty.empty()) {
        lastMeta.hasStopOnEmpty = true;
        lastMeta.stopOnEmpty = stopOnEmpty == "true" || stopOnEmpty == "TRUE";
    }
    lastMeta.rateLimitPolicyRaw = headerValue(headers, "ratelimit-policy");
    lastMeta.rateLimitRaw = headerValue(headers, "ratelimit");
    lastMeta.balanceLimitCents = parseLong(structuredValue(lastMeta.rateLimitPolicyRaw, "billing-balance", "q"));
    lastMeta.balanceRemainingCents = parseLong(structuredValue(lastMeta.rateLimitRaw, "billing-balance", "r"));
    lastMeta.quotaLimitCredits = parseLong(structuredValue(lastMeta.rateLimitPolicyRaw, "billing-quota", "q"));
    lastMeta.quotaRemainingCredits = parseLong(structuredValue(lastMeta.rateLimitRaw, "billing-quota", "r"));
    lastMeta.visitorQuotaLimitCredits = parseLong(structuredValue(lastMeta.rateLimitPolicyRaw, "visitor-quota", "q"));
    lastMeta.visitorQuotaRemainingCredits = parseLong(structuredValue(lastMeta.rateLimitRaw, "visitor-quota", "r"));
}

#ifdef _WIN32
inline std::wstring Client::widen(const std::string& input) {
    if (input.empty()) return {};
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), nullptr, 0);
    std::wstring wide(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), wide.data(), size_needed);
    return wide;
}

inline std::string Client::narrow(const std::wstring& input) {
    if (input.empty()) return {};
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), nullptr, 0, nullptr, nullptr);
    std::string out(size_needed, '\0');
    WideCharToMultiByte(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), out.data(), size_needed, nullptr, nullptr);
    return out;
}

inline std::string Client::queryHeaderValue(HINTERNET hRequest, const wchar_t* headerName) {
    DWORD size = 0;
    WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CUSTOM, headerName, WINHTTP_NO_OUTPUT_BUFFER, &size, WINHTTP_NO_HEADER_INDEX);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER || size == 0) return {};
    std::wstring buffer(size / sizeof(wchar_t), L'\0');
    if (!WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CUSTOM, headerName, buffer.data(), &size, WINHTTP_NO_HEADER_INDEX)) return {};
    if (!buffer.empty() && buffer.back() == L'\0') buffer.pop_back();
    return narrow(buffer);
}

inline std::string Client::sendWinHttp(const std::string& method, const std::string& pathAndQuery, const std::string& body) const {
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

    std::wstring requestHeaders = L"Accept: application/json\r\n";
    if (!token.empty()) requestHeaders += L"Authorization: Bearer " + widen(token) + L"\r\n";
    if (!body.empty()) requestHeaders += L"Content-Type: application/json\r\n";
    
    LPVOID bodyData = body.empty() ? WINHTTP_NO_REQUEST_DATA : (LPVOID)body.c_str();
    DWORD bodyLen = body.empty() ? 0 : static_cast<DWORD>(body.length());
    
    if (!WinHttpSendRequest(hRequest, requestHeaders.c_str(), static_cast<DWORD>(requestHeaders.length()), bodyData, bodyLen, bodyLen, 0)) {
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
    std::map<std::string, std::string> responseHeaders;
    auto storeHeader = [&](const char* key, const wchar_t* headerName) {
        auto value = queryHeaderValue(hRequest, headerName);
        if (!value.empty()) responseHeaders[key] = value;
    };
    storeHeader("x-request-id", L"X-Request-ID");
    storeHeader("retry-after", L"Retry-After");
    storeHeader("uapi-debit-status", L"UAPI-Debit-Status");
    storeHeader("uapi-credits-requested", L"UAPI-Credits-Requested");
    storeHeader("uapi-credits-charged", L"UAPI-Credits-Charged");
    storeHeader("uapi-credits-pricing", L"UAPI-Credits-Pricing");
    storeHeader("uapi-quota-active-buckets", L"UAPI-Quota-Active-Buckets");
    storeHeader("uapi-stop-on-empty", L"UAPI-Stop-On-Empty");
    storeHeader("ratelimit-policy", L"RateLimit-Policy");
    storeHeader("ratelimit", L"RateLimit");
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
    setMetaFromHeaders(responseHeaders);
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

inline std::string Client::sendCurl(const std::string& method, const std::string& absoluteUrl, const std::string& body) const {
    std::string cmd = "curl -s -S -D - -w \"\\n%{http_code}\" -X " + method + " " + shellEscape(absoluteUrl) + " -H \"Accept: application/json\"";
    if (!token.empty()) cmd += " -H " + shellEscape("Authorization: Bearer " + token);
    if (!body.empty()) {
        cmd += " -H \"Content-Type: application/json\"";
        cmd += " -d " + shellEscape(body);
    }
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
    std::string responseWithHeaders = output.substr(0, pos);
    std::string statusLine = output.substr(pos + 1);
    int status = std::stoi(statusLine);
    std::map<std::string, std::string> headers;
    std::string respBody = responseWithHeaders;
    auto split = responseWithHeaders.find("\r\n\r\n");
    std::size_t separatorLen = 4;
    if (split == std::string::npos) {
        split = responseWithHeaders.find("\n\n");
        separatorLen = 2;
    }
    if (split != std::string::npos) {
        auto headerBlock = responseWithHeaders.substr(0, split);
        respBody = responseWithHeaders.substr(split + separatorLen);
        std::stringstream hs(headerBlock);
        std::string line;
        while (std::getline(hs, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            auto colon = line.find(':');
            if (colon == std::string::npos) continue;
            auto key = line.substr(0, colon);
            auto value = line.substr(colon + 1);
            while (!key.empty() && std::isspace(static_cast<unsigned char>(key.back()))) key.pop_back();
            while (!value.empty() && std::isspace(static_cast<unsigned char>(value.front()))) value.erase(value.begin());
            std::transform(key.begin(), key.end(), key.begin(), [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
            headers[key] = value;
        }
    }
    setMetaFromHeaders(headers);
    if (status >= 400) {
        raiseError(status, respBody);
    }
    return respBody;
}
#endif

} // namespace
