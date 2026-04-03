# uapi-sdk-cpp

![Banner](https://raw.githubusercontent.com/AxT-Team/uapi-sdk-cpp/main/banner.png)

[![C++](https://img.shields.io/badge/C++-17+-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Docs](https://img.shields.io/badge/Docs-uapis.cn-2EAE5D?style=flat-square)](https://uapis.cn/)

> [!NOTE]
> 所有接口的 C++ 示例都可以在 [UApi](https://uapis.cn/docs/introduction) 的接口文档页面，向下滚动至 **快速启动** 区块后直接复制。

## 快速开始

```bash
git submodule add https://github.com/AxT-Team/uapi-sdk-cpp deps/uapi-cpp
```

```cpp
#include <uapi/Client.hpp>
#include <iostream>
#include <map>

int main() {
    uapi::Client client("https://uapis.cn", "YOUR_API_KEY");
    std::map<std::string, std::string> args{{"type", "weibo"}};
    auto result = client.misc().getMiscHotboard(args);
    std::cout << result << std::endl;
    return 0;
}
```

这个接口默认只要传 `type` 就可以拿当前热榜。`time`、`keyword`、`time_start`、`time_end`、`limit`、`sources` 都是按场景再传的可选参数。

## 特性

现在你不再需要反反复复的查阅文档了。

只需在 IDE 中键入 `client.`，所有核心模块——如 `Social()`、`Game()`、`Image()`——即刻同步展现。进一步输入即可直接定位到 `getSocialQqUserinfo` 这样的具体方法，其名称与文档的 `operationId` 严格保持一致，确保了开发过程的直观与高效。

所有方法签名只接受真实且必需的参数。当你在构建请求时，IDE 会即时提示 `qq`、`username` 等键名，这彻底杜绝了在 `std::map<std::string, std::string>` 中因键名拼写错误而导致的运行时错误。

针对 401、404、429 等标准 HTTP 响应，SDK 已将其统一映射为具名的错误类型。这些错误均附带 `code`、`status`、`details` 等关键上下文信息，确保你在日志中能第一时间准确、快速地诊断问题。

当前通过 `uapi::Client(baseUrl, token)` 配置 BaseURL 和 Token。如果你需要代理、超时或其他 HTTP 策略，建议按需修改源码，或者在项目里再封装一层。

如果你需要查看字段细节或内部逻辑，仓库中的 `./internal` 目录同步保留了由 `openapi-generator` 生成的完整结构体，随时可供参考。

## 响应元信息

每次请求完成后，SDK 会自动把响应 Header 解析成结构化的 `ResponseMeta`，你不用自己拆原始字符串。

成功时可以通过 `client.lastResponseMeta()` 读取，失败时可以通过 `e.meta` 读取，两条路径拿到的是同一套字段。

```cpp
#include <uapi/Client.hpp>
#include <iostream>
#include <map>

int main() {
    uapi::Client client("https://uapis.cn", "YOUR_API_KEY");
    std::map<std::string, std::string> args{{"qq", "10001"}};

    // 成功路径
    client.social().getSocialQqUserinfo(args);
    const auto& meta = client.lastResponseMeta();
    if (meta.creditsRequested >= 0) {
        std::cout << "这次请求原价: " << meta.creditsRequested << " 积分\n";
    }
    if (meta.creditsCharged >= 0) {
        std::cout << "这次实际扣费: " << meta.creditsCharged << " 积分\n";
    }
    if (!meta.creditsPricing.empty()) {
        std::cout << "特殊计价: " << meta.creditsPricing << '\n';
    }
    if (meta.balanceRemainingCents >= 0) {
        std::cout << "余额剩余: " << meta.balanceRemainingCents << " 分\n";
    }
    if (meta.quotaRemainingCredits >= 0) {
        std::cout << "资源包剩余: " << meta.quotaRemainingCredits << " 积分\n";
    }
    if (meta.activeQuotaBuckets >= 0) {
        std::cout << "当前有效额度桶: " << meta.activeQuotaBuckets << '\n';
    }
    if (meta.hasStopOnEmpty) {
        std::cout << "额度用空即停: " << (meta.stopOnEmpty ? "true" : "false") << '\n';
    }
    if (meta.billingKeyRateLimit >= 0) {
        std::cout << "Key QPS: " << meta.billingKeyRateRemaining << " / " << meta.billingKeyRateLimit
                  << ' ' << (meta.billingKeyRateUnit.empty() ? "req" : meta.billingKeyRateUnit) << '\n';
    }
    std::cout << "Request ID: " << meta.requestId << '\n';

    // 失败路径
    try {
        client.social().getSocialQqUserinfo(args);
    } catch (const uapi::UapiError& e) {
        std::cout << "Retry-After 秒数: " << e.meta.retryAfterSeconds << '\n';
        std::cout << "Retry-After 原始值: " << e.meta.retryAfterRaw << '\n';
        std::cout << "访客 QPS: " << e.meta.visitorRateRemaining << " / " << e.meta.visitorRateLimit << '\n';
        std::cout << "Request ID: " << e.meta.requestId << '\n';
    }

    return 0;
}
```

常用字段一览：

| 字段 | 说明 |
|------|------|
| `creditsRequested` | 这次请求原本要扣多少积分，也就是请求价 |
| `creditsCharged` | 这次请求实际扣了多少积分 |
| `creditsPricing` | 特殊计价原因，例如缓存半价 `cache-hit-half-price` |
| `balanceRemainingCents` | 账户余额剩余（分） |
| `quotaRemainingCredits` | 资源包剩余积分 |
| `activeQuotaBuckets` | 当前还有多少个有效额度桶参与计费 |
| `stopOnEmpty` | 额度耗尽后是否直接停止服务 |
| `retryAfterSeconds` / `retryAfterRaw` | 限流后的等待时长；当服务端返回 HTTP 时间字符串时看 `retryAfterRaw` |
| `requestId` | 请求唯一 ID，排障时使用 |
| `billingKeyRateLimit` / `billingKeyRateRemaining` | Billing Key 当前 QPS 规则的上限与剩余 |
| `billingIpRateLimit` / `billingIpRateRemaining` | Billing Key 单 IP 当前 QPS 规则的上限与剩余 |
| `visitorRateLimit` / `visitorRateRemaining` | 访客当前 QPS 规则的上限与剩余 |
| `rateLimitPolicies` / `rateLimits` | 完整结构化限流策略数据 |

## 错误模型概览

| HTTP 状态码 | SDK 错误类型            | 附加信息                     |
|-------------|------------------------|------------------------------|
| 401/403     | `UnauthorizedError`    | `code`、`status`、`details`  |
| 404         | `NotFoundError`        | `code`、`status`、`details`  |
| 400         | `InvalidParameterError` / `InvalidParamsError` | `code`、`status`、`details` |
| 429         | `ServiceBusyError`     | `code`、`status`             |
| 5xx         | `InternalServerErrorError` | `code`、`status`、`details` |
| 其他 4xx/5xx| `UapiError` / `ApiErrorError` | `code`、`status`、`details` |

## 其他 SDK

| 语言        | 仓库地址                                                     |
|-------------|--------------------------------------------------------------|
| Go          | https://github.com/AxT-Team/uapi-sdk-go                      |
| Python      | https://github.com/AxT-Team/uapi-sdk-python                  |
| TypeScript| https://github.com/AxT-Team/uapi-sdk-typescript           |
| Browser (TypeScript/JavaScript)| https://github.com/AxT-Team/uapi-browser-sdk        |
| Java        | https://github.com/AxT-Team/uapi-sdk-java                    |
| PHP         | https://github.com/AxT-Team/uapi-sdk-php                     |
| C#          | https://github.com/AxT-Team/uapi-sdk-csharp                  |
| C++（当前）        | https://github.com/AxT-Team/uapi-sdk-cpp                     |
| Rust        | https://github.com/AxT-Team/uapi-sdk-rust                    |

## 文档

访问 [UApi文档首页](https://uapis.cn/docs/introduction) 并选择任意接口，向下滚动到 **快速启动** 区块即可看到最新的 C++ 示例代码。


