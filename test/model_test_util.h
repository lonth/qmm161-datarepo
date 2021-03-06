#ifndef _MODEL_TEST_UTIL_
#define _MODEL_TEST_UTIL_

#include <gtest/gtest.h>
#include "cjson/cJSON.h"

extern "C" {
#include "data_parser.h"
#include "model_parser.h"
}

class ModelTestUtil
{
public:
    void assert_model_mo(const char *name, struct mds_node *node)
    {
        ASSERT_TRUE(NULL != node);
        ASSERT_STREQ(name, node->name);
        ASSERT_EQ(MDS_MT_CONTAINER, node->mtype);
    }

    void assert_model_list(const char *name, struct mds_node *node)
    {
        ASSERT_TRUE(NULL != node);
        ASSERT_STREQ(name, node->name);
        ASSERT_EQ(MDS_MT_LIST, node->mtype);
    }

    void assert_model_leaf(const char *name, mds_dtype dtype, struct mds_node *node)
    {
        ASSERT_TRUE(NULL != node);

        struct mds_leaf *leaf = (struct mds_leaf*) node;

        ASSERT_STREQ(name, leaf->name);
        ASSERT_EQ(MDS_MT_LEAF, leaf->mtype);
        ASSERT_EQ(dtype, leaf->dtype);
    }

    void assert_data_container(const char *name, struct mdd_node *node)
    {
        ASSERT_EQ(MDS_MT_CONTAINER, node->schema->mtype);
        ASSERT_STREQ(name, node->schema->name);
    }

    void assert_data_list(const char *name, struct mdd_node *node)
    {
        ASSERT_EQ(MDS_MT_LIST, node->schema->mtype) << "name:" << name << " vs " << node->schema->name;
        ASSERT_STREQ(name, node->schema->name) << "name:" << name << " vs " << node->schema->name;
    }

    void assert_data_string_leaf(const char *name, const char *value, struct mdd_node *node)
    {
        ASSERT_EQ(MDS_MT_LEAF, node->schema->mtype);
        ASSERT_EQ(MDS_DT_STR, ((struct mds_leaf*) node->schema)->dtype);
        ASSERT_STREQ(name, node->schema->name);

        struct mdd_leaf *leaf = (struct mdd_leaf*) node;
        ASSERT_STREQ(value, leaf->value.strv);
    }

    void assert_data_int_leaf(const char *name, long long value, struct mdd_node *node)
    {
        ASSERT_EQ(MDS_MT_LEAF, node->schema->mtype);
        ASSERT_EQ(MDS_DT_INT, ((struct mds_leaf*) node->schema)->dtype);
        ASSERT_STREQ(name, node->schema->name);

        struct mdd_leaf *leaf = (struct mdd_leaf*) node;
        ASSERT_EQ(value, leaf->value.intv);
    }

    void assert_equal_json(const char *expect, const char *target)
    {
        ASSERT_NE((const char*) NULL, expect);
        ASSERT_NE((const char*) NULL, target);

        cJSON *expectJs = cJSON_Parse(expect);
        cJSON *targetJs = cJSON_Parse(target);

        char *expectDump = cJSON_PrintUnformatted(expectJs);
        char *targetDump = cJSON_PrintUnformatted(targetJs);
        ASSERT_STREQ(expectDump, targetDump);

        free(expectDump);
        free(targetDump);

        cJSON_Delete(expectJs);
        cJSON_Delete(targetJs);
    }
};

#endif
