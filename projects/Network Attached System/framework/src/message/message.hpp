/* -------------------------------------------------------------------------- *
 * FILENAME      -    MessageHeader.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    25/12/22
 * -------------------------------------------------------------------------- */

#ifndef __MessageHeader_HPP__
#define __MessageHeader_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>
#include <string>
#include <linux/nbd.h>

#include "../event/event.hpp"

namespace ilrd
{

    enum MESSAGE_TYPE
    {
        READ_MSG,
        WRITE_MSG,
        ACK_MSG,
        READ_ACK,
        WRITE_ACK
    };

    static const size_t m_uid_size_g = sizeof(u_int64_t);

    class MessageHeader
    {
    public:
        explicit MessageHeader(MESSAGE_TYPE type);
        explicit MessageHeader(MESSAGE_TYPE type, const UID &uid, size_t offset, size_t bytes);
        virtual ~MessageHeader() = 0;
        MESSAGE_TYPE GetType() const;
        UID GetUid() const;
        size_t GetOffset() const;
        size_t GetBytes() const;
        virtual void Deserialize(char *buffer);
        virtual void Serialize(char *buffer);

        args_t GetArgs() const
        {
            return m_args;
        }
        char *GetDataToSend() const
        {
            return m_to_send;
        }

    private:
        args_t m_args;
        char *m_to_send;
        static u_int64_t m_uid;
        MESSAGE_TYPE m_type;
        UID m_uid;
        size_t m_offset;
        size_t m_bytes;
    };

    class SendWriteMessage : public MessageHeader
    {
    public:
        SendWriteMessage();
        SendWriteMessage(const UID &uid, char *buffer, size_t offset = 0, size_t bytes = 0);
        void Serialize(char *buffer);
        void Deserialize(char *buffer);
        char *GetBuffer();
        static MessageHeader *CreateSendWriteMsg();

    private:
        char *m_buffer;
    };

    class SendReadMessage : public MessageHeader
    {
    public:
        SendReadMessage();
        SendReadMessage(const UID &uid, size_t offset, size_t bytes);
        void Serialize(char *buffer);
        void Deserialize(char *buffer);
        static MessageHeader *CreateSendReadMsg();
    };

    class ReadAnsMessage : public MessageHeader
    {
    public:
        ReadAnsMessage();
        ReadAnsMessage(const UID &uid, char *buffer, size_t offset, size_t bytes);
        void Serialize(char *buffer);
        void Deserialize(char *buffer);
        char *GetBuffer();
        static MessageHeader *CreateReadAnsMsg();

    private:
        char *m_buffer;
    };

    class WriteAnsMessage : public MessageHeader
    {
    public:
        WriteAnsMessage();
        WriteAnsMessage(const UID &uid, size_t offset, size_t bytes);
        void Serialize(char *buffer);
        void Deserialize(char *buffer);
        static MessageHeader *CreateWriteAnsMsg();
    };
}

#endif // MessageHeader_HPP