/*
==========================================================================
 CHANGE LOG
==========================================================================
 Date       | Author        | Task ID | Description
------------+---------------+---------+-----------------------------------
 2026-11-20 | Diego Vaccher | TB-14   | Definition of Database Objects Model
==========================================================================
*/

#ifndef TB_MODELS_DBO_COMMON_HPP
#define TB_MODELS_DBO_COMMON_HPP

#include <Wt/Dbo/Dbo.h>
#include <Wt/WDateTime.h>
#include <Wt/Dbo/WtSqlTraits.h>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#define DEF_WT_DBO_STRING_TRAIT(full_class)                   \
namespace Wt::Dbo                                             \
{                                                             \
template<>                                                    \
struct dbo_traits<full_class> : public dbo_default_traits     \
{                                                             \
    using IdType = std::string;                               \
    static IdType invalidId() { return std::string(); }       \
    static const char* surrogateIdField() { return nullptr; } \
};                                                            \
} // #define DEF_WT_DBO_STRING_TRAIT

namespace tb::models::dbo
{

class BaseObject;

} // ns tb::models::dbo

/*
    Note(https://www.webtoolkit.eu/wt/doc/reference/html/structWt_1_1Dbo_1_1dbo__traits.html):
    >> The safe pattern to define traits is before the class definition,
    >> based on a forward declaration. This is necessary since the persist()
    >> function relies on this specialization.
*/
DEF_WT_DBO_STRING_TRAIT(tb::models::dbo::BaseObject);

namespace tb::models::dbo
{

class BaseObject
{
public:
    BaseObject()
    {
        static thread_local boost::uuids::random_generator gen;
        m_guid = boost::uuids::to_string(gen());
    }

    template<class Action>
    void persist(Action& action)
    {
        // Auto-update timestamps when writing to database
        if (!action.getsValue())
        {
            m_updatedOn = Wt::WDateTime::currentDateTime();
            if (m_createdOn.isNull())
            {
                m_createdOn = m_updatedOn;
            }
        }

        Wt::Dbo::id(action, m_guid, "guid", 36);
        Wt::Dbo::field(action, m_createdOn, "created_on");
        Wt::Dbo::field(action, m_updatedOn, "updated_on");
    }

    inline const std::string& GetId() const { return m_guid; }
    inline const Wt::WDateTime& GetCreatedOn() const { return m_createdOn; }
    inline const Wt::WDateTime& GetUpdatedOn() const { return m_updatedOn; }

protected:
    std::string m_guid;
    Wt::WDateTime m_createdOn;
    Wt::WDateTime m_updatedOn;
}; // cl BaseObject

} // ns tb::models::dbo

#endif