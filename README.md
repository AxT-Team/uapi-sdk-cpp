# uapi-sdk-cpp

![Banner](./banner.png)

[![C++](https://img.shields.io/badge/C++-20-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Docs](https://img.shields.io/badge/Docs-uapis.cn-2EAE5D?style=flat-square)](https://uapis.cn/)

> [!NOTE]
> 所有接口的 C++ 示例都可以在 [UApi](https://uapis.cn/docs/introduction) 的接口文档页面，向下滚动至 **快速启动** 区块后直接复制。

## 快速开始

```bash
git submodule add https://github.com/AxT-Team/uapi-cpp-sdk deps/uapi-cpp
```

```cpp
#include <uapi/Client.hpp>
#include <iostream>
#include <unordered_map>

int main() {
    uapi::Client client("https://uapis.cn/api/v1", "");
    std::unordered_map<std::string, std::string> args;
    args["qq"] = "10001";
    auto result = client.social().getSocialQqUserinfo(args);
    std::cout << result << std::endl;
    return 0;
}
```

## 特性

现在你不再需要反反复复的查阅文档了。

只需在 IDE 中键入 `client.`，所有核心模块——如 `Social()`、`Game()`、`Image()`——即刻同步展现。进一步输入即可直接定位到 `getSocialQqUserinfo` 这样的具体方法，其名称与文档的 `operationId` 严格保持一致，确保了开发过程的直观与高效。

所有方法签名只接受真实且必需的参数。当你在构建请求时，IDE 会即时提示 `qq`、`username` 等键名，这彻底杜绝了在 `std::unordered_map<std::string, std::string>` 中因键名拼写错误而导致的运行时错误。

针对 401、404、429 等标准 HTTP 响应，SDK 已将其统一映射为具名的错误类型。这些错误均附带 `code`、`status`、`details` 等关键上下文信息，确保你在日志中能第一时间准确、快速地诊断问题。

基础域名、请求超时和 `User-Agent` 已预设为合理的默认值。但你完全拥有控制权，可以通过 `uapi::Client(baseUrl, token)` 及其可插拔 HTTP 实现灵活覆盖 Token、BaseURL 等配置。

如果你需要查看字段细节或内部逻辑，仓库中的 `./internal` 目录同步保留了由 `openapi-generator` 生成的完整结构体，随时可供参考。

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
| Go          | https://github.com/AxT-Team/uapi-go-sdk                      |
| Python      | https://github.com/AxT-Team/uapi-python-sdk                  |
| TypeScript| https://github.com/AxT-Team/uapi-typescript-sdk           |
| Browser (TypeScript/JavaScript)| https://github.com/AxT-Team/uapi-browser-sdk        |
| Java        | https://github.com/AxT-Team/uapi-java-sdk                    |
| PHP         | https://github.com/AxT-Team/uapi-php-sdk                     |
| C#          | https://github.com/AxT-Team/uapi-csharp-sdk                  |
| C++（当前）        | https://github.com/AxT-Team/uapi-cpp-sdk                     |
| Rust        | https://github.com/AxT-Team/uapi-rust-sdk                    |

## 文档

访问 [UApi文档首页](https://uapis.cn/docs/introduction) 并选择任意接口，向下滚动到 **快速启动** 区块即可看到最新的 C++ 示例代码。
