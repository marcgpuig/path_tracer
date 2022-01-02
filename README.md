# CPU C++ Path Tracer
Based on the amazing [Ray Tracing in One Weekend](https://raytracing.github.io/).

# How to use it

### Windows

Using a [Visual Studio Native Tools Command Prompt](https://docs.microsoft.com/en-us/dotnet/framework/tools/developer-command-prompt-for-vs) go to the project path and type:
```
make nmake
make run
```

### Linux

There is a basic port to bazel, now you can run it with:
```
bazel run //src:main
```