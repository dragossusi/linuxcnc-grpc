package ro.dragossusi.grpc.linuxcnc

import io.grpc.ManagedChannelBuilder
import ro.dragossusi.proto.linuxcnc.CreateComponentRequest
import ro.dragossusi.proto.linuxcnc.GetComponentsRequest
import ro.dragossusi.proto.linuxcnc.GetComponentsResponse
import ro.dragossusi.proto.linuxcnc.LinuxCncGrpc
import java.util.concurrent.TimeUnit
import java.util.logging.Level
import java.util.logging.Logger

private val logger = Logger.getLogger("Main")

fun main() {
    val channel = ManagedChannelBuilder.forTarget("localhost:50051")
        .usePlaintext()
        .build()
    try {
        val service = LinuxCncGrpc.newBlockingStub(channel)
        service.addComp()
        service.getComp()
    } finally {
        channel.shutdownNow()
            .awaitTermination(5, TimeUnit.SECONDS)
    }
}

private fun LinuxCncGrpc.LinuxCncBlockingStub.addComp() {
    val component = createComponent(
        CreateComponentRequest.newBuilder()
            .setName("test_comp")
            .build()
    )
    logger.info("Created component: $component")
}

private fun LinuxCncGrpc.LinuxCncBlockingStub.getComp() {
    val components = getComponents(GetComponentsRequest.newBuilder().build())
    components.forEachRemaining { response: GetComponentsResponse ->
        val list = response.componentsList
        logger.info("Received ${list.size} components: $list")
    }
}