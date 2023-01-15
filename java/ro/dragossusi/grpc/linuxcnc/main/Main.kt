package ro.dragossusi.grpc.linuxcnc.main

import io.grpc.ManagedChannelBuilder
import ro.dragossusi.proto.linuxcnc.CreateComponentRequest
import ro.dragossusi.proto.linuxcnc.GetComponentsRequest
import ro.dragossusi.proto.linuxcnc.LinuxCncGrpc
import ro.dragossusi.proto.linuxcnc.ReadStatusRequest
import java.util.concurrent.TimeUnit
import java.util.logging.Logger

private val logger = Logger.getLogger("Main")

fun main() {
    val channel = ManagedChannelBuilder.forTarget("localhost:50051")
        .usePlaintext()
        .build()
    try {
        LinuxCncGrpc.newBlockingStub(channel).apply {
//            addComp()
//            getComp()
            readStatus()
        }
    } finally {
        channel.shutdownNow()
            .awaitTermination(5, TimeUnit.SECONDS)
    }
}

private fun LinuxCncGrpc.LinuxCncBlockingStub.readStatus() {
    val request = ReadStatusRequest.newBuilder().build()
    val status = readStatus(request)

    logger.info("Status: \n$status")
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
        .componentsList
    logger.info("Received ${components.size} components: $components")
}