#pragma once

#include "core/modification/AddBytesCommand.hpp"
#include "core/modification/bytes/InsertedBytesRepository.hpp"
#include "core/modification/section/SectionQuery.hpp"
#include "shared/message/IMessageBus.hpp"

class CAddBytesHandler
{
    IMessageBus* m_messageBus;
    ISectionQuery* m_sectionQuery;
    IInsertedBytesRepository* m_bytesRepository;

public:
    CAddBytesHandler(IMessageBus* messageBus, ISectionQuery* sectionQuery, IInsertedBytesRepository* bytesRepository);
    void handle(const CAddBytesCommand& command) const;
};
