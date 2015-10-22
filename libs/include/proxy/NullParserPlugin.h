#ifndef PROXY_NULLPARSERPLUGIN_H
#define PROXY_NULLPARSERPLUGIN_H

#include "proxy/ParserPlugin.h"
#include "proxy/Uncopyable.h"
#include "proxy/Buffer.h"

namespace proxy {

    class NullParserPlugin final : public IParser
    {
        public:

        NullParserPlugin(size_t bufferSize, IParserCallbacks& callbacks);

        virtual bool Parse(const RSlice& input) override;

        virtual WSlice GetWriteSlice() override;

        private:


        Buffer m_buffer;
        IParserCallbacks& m_callbacks;
    };

    class NullParserPluginFactory final : public IParserFactory, private Uncopyable
    {
    public:

        NullParserPluginFactory(size_t bufferSize = 4096);

    private:

        virtual std::unique_ptr<IParser> Create(IParserCallbacks& callbacks) override;

        NullParserPluginFactory() = delete;

        const size_t M_BUFFER_SIZE;
    };

}

#endif //PROXY_NULLPARSERPLUGIN_H